-- Car profile
--local find_access_tag = require("lib/access").find_access_tag
function find_access_tag(source,access_tags_hierarchy)
    for i,v in ipairs(access_tags_hierarchy) do
        local tag = source:get_value_by_key(v)
        if tag and tag ~= '' then
            return tag
        end
    end
    return ""
end


--local get_destination = require("lib/destination").get_destination
function get_destination(way)
    local destination = way:get_value_by_key("destination")
    local destination_ref = way:get_value_by_key("destination:ref")

    -- Assemble destination as: "A59: Düsseldorf, Köln"
    --          destination:ref  ^    ^  destination

    local rv = ""

    if destination_ref and destination_ref ~= "" then
        rv = rv .. string.gsub(destination_ref, ";", ", ")
    end

    if destination and destination ~= "" then
        if rv ~= "" then
            rv = rv .. ": "
        end

        rv = rv .. string.gsub(destination, ";", ", ")
    end

    return rv
end


--local set_classification = require("lib/guidance").set_classification
--local get_turn_lanes = require("lib/guidance").get_turn_lanes

-- Guidance: Default Mapping from roads to types/priorities
highway_classes = { ["motorway"] = road_priority_class.motorway,
    ["motorway_link"] = road_priority_class.link_road,
    ["trunk"] = road_priority_class.trunk,
    ["trunk_link"] = road_priority_class.link_road,
    ["primary"] = road_priority_class.primary,
    ["primary_link"] = road_priority_class.link_road,
    ["secondary"] = road_priority_class.secondary,
    ["secondary_link"] = road_priority_class.link_road,
    ["tertiary"] = road_priority_class.tertiary,
    ["tertiary_link"] = road_priority_class.link_road,
    ["unclassified"] = road_priority_class.side_residential,
    ["residential"] = road_priority_class.side_residential,
    ["service"] = road_priority_class.connectivity,
    ["living_street"] = road_priority_class.main_residential,
    ["track"] = road_priority_class.bike_path,
    ["path"] = road_priority_class.bike_path,
    ["footway"] = road_priority_class.foot_path,
    ["pedestrian"] = road_priority_class.foot_path,
    ["steps"] = road_priority_class.foot_path}

default_highway_class = road_priority_class.connectivity;

motorway_types = { ["motorway"] = true, ["motorway_link"] = true, ["trunk"] = true, ["trunk_link"] = true }

-- these road types are set with a car in mind. For bicycle/walk we probably need different ones
road_types = { ["motorway"] = true,
    ["motorway_link"] = true,
    ["trunk"] = true,
    ["trunk_link"] = true,
    ["primary"] = true,
    ["primary_link"] = true,
    ["secondary"] = true,
    ["secondary_link"] = true,
    ["tertiary"] = true,
    ["tertiary_link"] = true,
    ["unclassified"] = true,
    ["residential"] = true,
    ["living_street"] = true }

link_types = { ["motorway_link"] = true, ["trunk_link"] = true, ["primary_link"] = true, ["secondary_link"] = true, ["tertiary_link"] = true }

-- Read predicted one-way results from csv
customized_way_speed_forward = {}
customized_way_speed_backward = {}
customized_way_removal_forward = {}
customized_way_removal_backward = {}

function read_customized_way_speed(path)
    local file = io.open(path, "r")
    if not file then
        print("WARN: can't read from ", path)
        return
    end
    for line in file:lines() do
        local wayid, speed, remark, direction = line:match("%s*(.-),%s*(.-),%s*(.-),%s*(.-)$")
        if tonumber(speed) ~= nil and tonumber(direction) ~= nil then
            speed = tonumber(speed)
            direction = tonumber(direction)
            if direction ~= 1 and direction ~= -1 then
                print("WARN: direction has to be 1 (forward) or -1 (backward). direction=", direction)
            else
                if speed <= 0 then
                    if direction == 1 then
                        customized_way_removal_forward[wayid] = true
                    else
                        customized_way_removal_backward[wayid] = true
                    end
                else
                    if direction == 1 then
                        customized_way_speed_forward[wayid] = speed
                    else
                        customized_way_speed_backward[wayid] = speed
                    end
                end
            end
        else
            print("WARN: can't convert speed to float or direction to 1 or -1. Speed = ", speed, "Direction = ", direction)
        end
    end
    file:close()
end

function read_customized_way_removal(path)
    local file = io.open(path, "r")
    if not file then
        print("WARN: can't read from ", path)
        return
    end
    for line in file:lines() do
        customized_way_removal_forward[line] = true
        customized_way_removal_backward[line] = true
    end
    file:close()
end

print("read customized way speed from csv")
read_customized_way_speed("speed_profile.csv")
print("read customized way removal from csv")
read_customized_way_removal("way_removal.csv")

function set_classification (highway, result)
    if motorway_types[highway] then
        result.road_classification.motorway_class = true;
    end
    if link_types[highway] then
        result.road_classification.link_class = true;
    end
    if highway_classes[highway] ~= nil then
        result.road_classification.road_priority_class = highway_classes[highway]
    else
        result.road_classification.road_priority_class = default_highway_class
    end
    if road_types[highway] then
        result.road_classification.may_be_ignored = false;
    else
        result.road_classification.may_be_ignored = true;
    end
end

-- returns forward,backward psv lane count
local function get_psv_counts(way)
    local psv = way:get_value_by_key("lanes:psv")
    local psv_forward = way:get_value_by_key("lanes:psv:forward");
    local psv_backward = way:get_value_by_key("lanes:psv:backward");

    local fw = 0;
    local bw = 0;
    if( psv and psv ~= "" ) then
        fw = tonumber(psv)
        if( fw == nil ) then
            fw = 0
        end
    end
    if( psv_forward and psv_forward ~= "" ) then
        fw = tonumber(psv_forward)
        if( fw == nil ) then
            fw = 0
        end
    end
    if( psv_backward and psv_backward ~= "" ) then
        bw = tonumber(psv_backward);
        if( bw == nil ) then
            bw = 0
        end
    end
    return fw, bw
end

-- trims lane string with regard to supported lanes
local function process_lanes(turn_lane,vehicle_lane,first_count,second_count)
    if turn_lane and turn_lane ~= "" then
        if vehicle_lane and vehicle_lane ~= "" then
            turn_lane = applyAccessTokens(turn_lane,vehicle_lane)
        elseif first_count ~= 0 or second_count ~= 0 then
            turn_lane = trimLaneString(turn_lane, first_count, second_count)
        end
    end
    return turn_lane;
end

-- this is broken for left-sided driving. It needs to switch left and right in case of left-sided driving
function get_turn_lanes(way)
    local fw_psv = 0
    local bw_psv = 0
    fw_psv, bw_psv = get_psv_counts(way)

    local turn_lanes = way:get_value_by_key("turn:lanes")
    local turn_lanes_fw = way:get_value_by_key("turn:lanes:forward")
    local turn_lanes_bw = way:get_value_by_key("turn:lanes:backward")

    local vehicle_lanes = way:get_value_by_key("vehicle:lanes");
    local vehicle_lanes_fw = way:get_value_by_key("vehicle:lanes:forward");
    local vehicle_lanes_bw = way:get_value_by_key("vehicle:lanes:backward");

    turn_lanes = process_lanes(turn_lanes,vehicle_lanes,bw_psv,fw_psv)
    turn_lanes_fw = process_lanes(turn_lanes_fw,vehicle_lanes_fw,bw_psv,fw_psv)
    --backwards turn lanes need to treat bw_psv as fw_psv and vice versa
    turn_lanes_bw = process_lanes(turn_lanes_bw,vehicle_lanes_bw,fw_psv,bw_psv)

    return turn_lanes, turn_lanes_fw, turn_lanes_bw
end




-- Begin of globals
barrier_whitelist = { ["cattle_grid"] = true, ["border_control"] = true, ["checkpoint"] = true, ["toll_booth"] = true, ["sally_port"] = true, ["gate"] = true, ["lift_gate"] = true, ["no"] = true, ["entrance"] = true }
access_tag_whitelist = { ["yes"] = true, ["private"] = true, ["motorcar"] = true, ["motor_vehicle"] = true, ["vehicle"] = true, ["permissive"] = true, ["designated"] = true, ["destination"] = true }
access_tag_blacklist = { ["no"] = true, ["agricultural"] = true, ["forestry"] = true, ["emergency"] = true, ["psv"] = true, ["delivery"] = true }
access_tag_restricted = { ["destination"] = true, ["delivery"] = true }
access_tags_hierarchy = { "motorcar", "motor_vehicle", "vehicle", "access" }
service_tag_restricted = { ["parking_aisle"] = true }
service_tag_forbidden = { ["emergency_access"] = true }
restriction_exception_tags = { "motorcar", "motor_vehicle", "vehicle" }

highway_whitelist = {
    "motorway",
    "motorway_link",
    "trunk",
    "trunk_link",
    "primary",
    "primary_link",
    "secondary",
    "secondary_link",
    "tertiary",
    "tertiary_link",
    "unclassified",
    "residential",
    "living_street",
    "service",
    --  "track",
    "ferry",
    "movable",
    --"shuttle_train",
    "default",
}

function in_highway_whitelist(tag)
    for i, v in ipairs(highway_whitelist) do
        if v == tag then
            return true
        end
    end
    return false
end

-- A list of suffixes to suppress in name change instructions
suffix_list = { "N", "NE", "E", "SE", "S", "SW", "W", "NW", "North", "South", "West", "East" }

speed_profile = {
  ["motorway"] = 50.210252228560002,
  ["motorway_link"] = 30.442746367840002,
  ["trunk"] = 38.910443051919998,
  ["trunk_link"] = 41.463545034719999,
  ["primary"] = 30.121716837280001,
  ["primary_link"] = 26.335761231272002,
  ["secondary"] = 26.828629389463998,
  ["secondary_link"] = 25.553861161440000,
  ["tertiary"] = 24.271965765887998,
  ["tertiary_link"] = 22.194191398904000,
  ["unclassified"] = 26.588079653855999,
  ["residential"] = 19.112178856160000,
  ["living_street"] = 7.616016031872000,
  ["service"] = 20.310053947280000,
  ["movable"] = 14.000000000000000,
  ["shuttle_train"] = 19.000000000000000,
  ["default"] = 11.000000000000000,
  ["private"] = 8.000000000000000
  -- Tuningid = 2eca4f41SIN_4W2019-06-27, date = 2019-06-27
}

route_speeds = {
    ["ferry"] = 5
}

-- service speeds
service_speeds = {
    ["alley"] = 5,
    ["parking_aisle"] = 5
}


-- set profile properties
properties.u_turn_penalty                  = 20
properties.traffic_signal_penalty          = 2
properties.use_turn_restrictions           = true
properties.continue_straight_at_waypoint   = true
properties.left_hand_driving               = false

local turn_penalty               = 7.5
-- Note: this biases right-side driving.  Should be
-- inverted for left-driving countries.
local turn_bias                  = properties.left_hand_driving and 1/1.075 or 1.075

local obey_oneway                = true
local ignore_areas               = true
local ignore_hov_ways            = true
local ignore_toll_ways           = false

local abs = math.abs
local min = math.min
local max = math.max

function get_name_suffix_list(vector)
    for index,suffix in ipairs(suffix_list) do
        vector:Add(suffix)
    end
end

function get_exceptions(vector)
    for i,v in ipairs(restriction_exception_tags) do
        vector:Add(v)
    end
end

function node_function (node, result)
    -- parse access and barrier tags
    local access = find_access_tag(node, access_tags_hierarchy)
    if access and access ~= "" then
        if access_tag_blacklist[access] then
            result.barrier = true
        end
    else
        local barrier = node:get_value_by_key("barrier")
        if barrier and "" ~= barrier then
            --  make an exception for rising bollard barriers
            local bollard = node:get_value_by_key("bollard")
            local rising_bollard = bollard and "rising" == bollard

            if not barrier_whitelist[barrier] and not rising_bollard then
                result.barrier = true
            end
        end
    end

    -- check if node is a traffic light
    local tag = node:get_value_by_key("highway")
    if tag and "traffic_signals" == tag then
        result.traffic_lights = true
    end
end

function way_function (way, result)
    local highway = way:get_value_by_key("highway")
    local route = way:get_value_by_key("route")
    local bridge = way:get_value_by_key("bridge")
    local wayid = tostring(way:id())

    if (route ~= "ferry") then
        if (not (highway and highway ~= "")) or (highway == "" and bridge and bridge ~= "") or highway == "track" or highway == "path" or highway == "footway" or highway == "pedestrian" or highway == "steps" or highway == "bus_stop" or highway == "cycleway" or highway == "construction" then
            return
        end
    end

    -- minbo filter out ways with non-empty route tag but keep route="ferry" with motor_vehicle="yes" or motorcar="yes"
    if (route and route ~= "")then
        if route ~= "ferry" then
            return
        end
        local motor_vehicle = way:get_value_by_key("motor_vehicle")
        local motorcar = way:get_value_by_key("motorcar")
        if not ((motor_vehicle and motor_vehicle == "yes") or (motorcar and motorcar == "yes")) then
            return
        end
    end

    -- default to driving mode, may get overwritten below
    result.forward_mode = mode.driving
    result.backward_mode = mode.driving

    if customized_way_removal_forward[wayid] ~= nil then
        print("Remove Way id=",wayid, "in forward direction")
        result.forward_mode = mode.inaccessible
    end

    if customized_way_removal_backward[wayid] ~= nil then
        print("Remove Way id=",wayid, "in backward direction")
        result.backward_mode = mode.inaccessible
    end

    -- we dont route over areas
    local area = way:get_value_by_key("area")
    if ignore_areas and area and "yes" == area then
        return
    end

    -- respect user-preference for toll=yes ways
    local toll = way:get_value_by_key("toll")
    if ignore_toll_ways and toll and "yes" == toll then
        return
    end

    -- treat oneway="reversible" as twoway
    local oneway = way:get_value_by_key("oneway")
    if oneway and "reversible" == oneway then
        oneway = ""
    end

    local impassable = way:get_value_by_key("impassable")
    if impassable and "yes" == impassable then
        return
    end

    local status = way:get_value_by_key("status")
    if status and "impassable" == status then
        return
    end

    -- Check if we are allowed to access the way
    local access = find_access_tag(way, access_tags_hierarchy)
    if access_tag_blacklist[access] then
        return
    end

    -- handling ferries and piers
    local route_speed = route_speeds[route]
    if (route_speed and route_speed > 0) then
        highway = route
        local duration  = way:get_value_by_key("duration")
        if duration and durationIsValid(duration) then
            result.duration = max( parseDuration(duration), 1 )
        end
        result.forward_mode = mode.ferry
        result.backward_mode = mode.ferry
        result.forward_speed = route_speed
        result.backward_speed = route_speed
    end

    -- handling movable bridges
    local bridge_speed = speed_profile[bridge]
    local capacity_car = way:get_value_by_key("capacity:car")
    if (bridge_speed and bridge_speed > 0) and (capacity_car ~= 0) then
        highway = bridge
        local duration  = way:get_value_by_key("duration")
        if duration and durationIsValid(duration) then
            result.duration = max( parseDuration(duration), 1 )
        end
        result.forward_speed = bridge_speed
        result.backward_speed = bridge_speed
    end

    -- leave early if this way is not accessible
    if "" == highway or not in_highway_whitelist(highway) then
        return
    end

    if result.forward_speed == -1 then
        local highway_speed = speed_profile[highway]
        -- Set the avg speed on the way if it is accessible by road class
        -- forward
        if customized_way_speed_forward[wayid] ~= nil then
            print("Customize speed",wayid, "forward", customized_way_speed_forward[wayid])
            result.forward_speed = customized_way_speed_forward[wayid]
        elseif access == "private" then
            result.forward_speed =speed_profile["private"]
            print("assign private road forward speed",wayid,result.forward_speed)
        elseif highway_speed then
            result.forward_speed = highway_speed
        else
            -- Set the avg speed on ways that are marked accessible
            if not access_tag_blacklist[access] then
                result.forward_speed = speed_profile["default"]
            end
        end
    end

    if result.backward_speed == -1 then
        local highway_speed = speed_profile[highway]
        -- backward
        if customized_way_speed_backward[wayid] ~= nil then
            print("Customize speed",wayid, "backward", customized_way_speed_backward[wayid])
            result.backward_speed = customized_way_speed_backward[wayid]
        elseif access == "private" then
            result.backward_speed =speed_profile["private"]
            print("assign private road backwawrd speed",wayid,result.forward_speed)
        elseif highway_speed then
            result.backward_speed = highway_speed
        else
            -- Set the avg speed on ways that are marked accessible
            if not access_tag_blacklist[access] then
                result.backward_speed = speed_profile["default"]
            end
        end
    end

    if -1 == result.forward_speed and -1 == result.backward_speed then
        return
    end

    -- set the road classification based on guidance globals configuration
    set_classification(highway,result)

    -- parse the remaining tags
    local name = way:get_value_by_key("name")
    local pronunciation = way:get_value_by_key("name:pronunciation")
    local ref = way:get_value_by_key("ref")
    local junction = way:get_value_by_key("junction")
    -- local barrier = way:get_value_by_key("barrier", "")
    -- local cycleway = way:get_value_by_key("cycleway", "")
    local service = way:get_value_by_key("service")

    -- Set the name that will be used for instructions
    local has_ref = ref and "" ~= ref
    local has_name = name and "" ~= name
    local has_pronunciation = pronunciation and "" ~= pronunciation

    if has_name then
        result.name = name
    end

    if has_ref then
        result.ref = ref
    end

    if has_pronunciation then
        result.pronunciation = pronunciation
    end

    local turn_lanes = ""
    local turn_lanes_forward = ""
    local turn_lanes_backward = ""

    turn_lanes, turn_lanes_forward, turn_lanes_backward = get_turn_lanes(way)
    if  turn_lanes and turn_lanes ~= "" then
        result.turn_lanes_forward = turn_lanes;
        result.turn_lanes_backward = turn_lanes;
    else
        if turn_lanes_forward and turn_lanes_forward ~= ""  then
            result.turn_lanes_forward = turn_lanes_forward;
        end

        if turn_lanes_backward and turn_lanes_backward ~= "" then
            result.turn_lanes_backward = turn_lanes_backward;
        end
    end


    if junction and "roundabout" == junction then
        result.roundabout = true
    end

    -- Set access restriction flag if access is allowed under certain restrictions only
    if access ~= "" and access_tag_restricted[access] then
        result.is_access_restricted = true
    end

    if service and service ~= "" then
        -- Set access restriction flag if service is allowed under certain restrictions only
        if service_tag_restricted[service] then
            result.is_access_restricted = true
        end

        -- Set don't allow access to certain service roads
        if service_tag_forbidden[service] then
            result.forward_mode = mode.inaccessible
            result.backward_mode = mode.inaccessible
            return
        end
    end

    -- Set direction according to tags on way
    if obey_oneway then
        if oneway == "-1" then
            result.forward_mode = mode.inaccessible
        elseif oneway == "yes" or
                oneway == "1" or
                oneway == "true" or
                junction == "roundabout" or
                (highway == "motorway" and oneway ~= "no") then
            result.backward_mode = mode.inaccessible

            -- If we're on a oneway and there is no ref tag, re-use destination tag as ref.
            local destination = get_destination(way)
            local has_destination = destination and "" ~= destination

            result.destinations = destination
        end
    end

    -- only allow this road as start point if it not a ferry
    result.is_startpoint = result.forward_mode == mode.driving or result.backward_mode == mode.driving
end

function turn_function (angle)
    -- Use a sigmoid function to return a penalty that maxes out at turn_penalty
    -- over the space of 0-180 degrees.  Values here were chosen by fitting
    -- the function to some turn penalty samples from real driving.
    -- multiplying by 10 converts to deci-seconds see issue #1318
    if angle>=0 then
        return 10 * turn_penalty / (1 + 2.718 ^ - ((13 / turn_bias) * angle/180 - 6.5*turn_bias))
    else
        return 10 * turn_penalty / (1 + 2.718 ^  - ((13 * turn_bias) * - angle/180 - 6.5/turn_bias))
    end
end
