-- Car profile

api_version = 4

--local Set 
function Set(source)
  set = {}
  if source then
    for i,v in ipairs(source) do
      set[v] = true
    end
  end
  return set
end

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

--local Sequence 
function Sequence(source)
  return source
end

--local Utils 
Utils = {}

-- split string 'a; b; c' to table with values ['a', 'b', 'c']
-- so it use just one separator ';'
function Utils.string_list_tokens(str)
  result = {}
  local idx = 0
  for s in str.gmatch(str, "([^;]*)") do
    if s ~= nil and s ~= '' then
      idx = idx + 1
      result[idx] = s:gsub("^%s*(.-)%s*$", "%1")
    end
  end

  return result
end

-- same as Utils.StringListTokens, but with many possible separators:
-- ',' | ';' | ' '| '(' | ')'
function Utils.tokenize_common(str)
  result = {}
  local idx = 0
  for s in str.gmatch(str, "%S+") do
    if s ~= nil and s ~= '' then
      idx = idx + 1
      result[idx] = s:gsub("^%s*(.-)%s*$", "%1")
    end
  end

  return result
end

-- returns true, if string contains a number
function Utils.is_number(str)
  return (tonumber(str) ~= nil)
end


--local tags
local Tags = {}

-- return [forward,backward] values for a specific tag.
-- e.g. for maxspeed search forward:
--   maxspeed:forward
--   maxspeed
-- and backward:
--   maxspeed:backward
--   maxspeed

function Tags.get_forward_backward_by_key(way,data,key)
  local forward = way:get_value_by_key(key .. ':forward')
  local backward = way:get_value_by_key(key .. ':backward')

  if not forward or not backward then
     local common = way:get_value_by_key(key)

     if (data.oneway) then
        if data.is_forward_oneway then
           forward = forward or common
        end
        if data.is_reverse_oneway then
           backward = backward or common
        end
     else
        forward = forward or common
        backward = backward or common
     end
  end

  return forward, backward
end

-- return [forward,backward] values, searching a
-- prioritized sequence of tags
-- e.g. for the sequence [maxspeed,advisory] search forward:
--   maxspeed:forward
--   maxspeed
--   advisory:forward
--   advisory
-- and for backward:
--   maxspeed:backward
--   maxspeed
--   advisory:backward
--   advisory

function Tags.get_forward_backward_by_set(way,data,keys)
  local forward, backward
  for i,key in ipairs(keys) do
    if not forward then
      forward = way:get_value_by_key(key .. ':forward')
    end
    if not backward then
      backward = way:get_value_by_key(key .. ':backward')
    end
    if not forward or not backward then
      local common = way:get_value_by_key(key)
      forward = forward or common
      backward = backward or common
    end
    if forward and backward then
      break
    end
  end

  return forward, backward
end

-- look through a sequence of keys combined with a prefix
-- e.g. for the sequence [motorcar,motor_vehicle,vehicle] and the prefix 'oneway' search for:
-- oneway:motorcar
-- oneway:motor_vehicle
-- oneway:vehicle

function Tags.get_value_by_prefixed_sequence(way,seq,prefix)
  local v
  for i,key in ipairs(seq) do
    v = way:get_value_by_key(prefix .. ':' .. key)
    if v then
      return v
    end
  end
end

-- check if key-value pairs are set in a way and return a
-- corresponding constant if it is. e.g. for this input:
--
-- local speeds = {
--  highway = {
--    residential =  19.112178856160000,
--    primary = 40
--  },
--  amenity = {
--    parking = 10
--  }
-- }
--
-- we would check whether the following key-value combinations
-- are set, and return the corresponding constant:
--
-- highway = residential      => 20
-- highway = primary          => 40
-- amenity = parking          => 10

function Tags.get_constant_by_key_value(way,lookup)
  for key,set in pairs(lookup) do
    local way_value = way:get_value_by_key(key)
    for value,t in pairs(set) do
      if way_value == value then
        return key,value,t
      end
    end
  end
end

--local Relations 
Relations = {}

function is_direction(role)
  return (role == 'north' or role == 'south' or role == 'west' or role == 'east')
end

-- match ref values to relations data
function Relations.match_to_ref(relations, ref)

  function calculate_scores(refs, tag_value)
    local tag_tokens = Set(Utils.tokenize_common(tag_value))
    local result = {}
    for i, r in ipairs(refs) do
      local ref_tokens = Utils.tokenize_common(r)
      local score = 0

      for _, t in ipairs(ref_tokens) do
        if tag_tokens[t] then
          if Utils.is_number(t) then
            score = score + 2
          else
            score = score + 1
          end
        end
      end

      result[r] = score
    end

    return result
  end

  local references = Utils.string_list_tokens(ref)
  local result_match = {}
  local order = {}
  for i, r in ipairs(references) do
    result_match[r] = { forward = nil, backward = nil }
    order[i] = r
  end

  for i, rel in ipairs(relations) do
    local name_scores = nil
    local name_tokens = {}
    local route_name = rel["route_name"]
    if route_name then
      name_scores = calculate_scores(references, route_name)
    end

    local ref_scores = nil
    local ref_tokens = {}
    local route_ref = rel["route_ref"]
    if route_ref then
      ref_scores = calculate_scores(references, route_ref)
    end

    -- merge scores
    local direction = rel["route_direction"]
    if direction then
      local best_score = -1
      local best_ref = nil

      function find_best(scores)
        if scores then
          for k ,v in pairs(scores) do
            if v > best_score then
              best_ref = k
              best_score = v
            end
          end
        end
      end

      find_best(name_scores)
      find_best(ref_scores)

      if best_ref then
        local result_direction = result_match[best_ref]

        local is_forward = rel["route_forward"]
        if is_forward == nil then
          result_direction.forward = direction
          result_direction.backward = direction
        elseif is_forward == true then
          result_direction.forward = direction
        else
          result_direction.backward = direction
        end

        result_match[best_ref] = result_direction
      end
    end

  end

  local result = {}
  for i, r in ipairs(order) do
    result[i] = { ref = r, dir = result_match[r] };
  end

  return result
end

function get_direction_from_superrel(rel, relations)
  local result = nil
  local result_id = nil
  local rel_id_list = relations:get_relations(rel)

  function set_result(direction, current_rel)
    if (result ~= nil) and (direction ~= nil) then
      print('WARNING: relation ' .. rel:id() .. ' is a part of more then one supperrelations ' .. result_id .. ' and ' .. current_rel:id())
      result = nil
    else
      result = direction
      result_id = current_rel:id()
    end
  end

  for i, rel_id in ipairs(rel_id_list) do
    local parent_rel = relations:relation(rel_id)
    if parent_rel:get_value_by_key('type') == 'route' then
      local role = parent_rel:get_role(rel)

      if is_direction(role) then
        set_result(role, parent_rel)
      else
        local dir = parent_rel:get_value_by_key('direction')
        if is_direction(dir) then
          set_result(dir, parent_rel)
        end
      end
    end
    -- TODO: support forward/backward
  end

  return result
end

function Relations.parse_route_relation(rel, way, relations)
  local t = rel:get_value_by_key("type")
  local role = rel:get_role(way)
  local result = {}

  function add_extra_data(m)
    local name = rel:get_value_by_key("name")
    if name then
      result['route_name'] = name
    end

    local ref = rel:get_value_by_key("ref")
    if ref then
      result['route_ref'] = ref
    end
  end

  if t == 'route' then
    local role_direction = nil
    local route = rel:get_value_by_key("route")
    if route == 'road' then
      -- process case, where directions set as role
      if is_direction(role) then
        role_direction = role
      end
    end

    local tag_direction = nil
    local direction = rel:get_value_by_key('direction')
    if direction then
      direction = string.lower(direction)
      if is_direction(direction) then
        tag_direction = direction
      end
    end

    -- determine direction
    local result_direction = role_direction
    if result_direction == nil and tag_direction ~= '' then
      result_direction = tag_direction
    end

    if role_direction ~= nil and tag_direction ~= nil and role_direction ~= tag_direction then
      result_direction = nil
      print('WARNING: conflict direction in role of way ' .. way:id() .. ' and direction tag in relation ' .. rel:id())
    end


    -- process superrelations
    local super_dir = get_direction_from_superrel(rel, relations)

    -- check if there are data error
    if (result_direction ~= nil) and (super_dir ~= nil) and (result_direction ~= super_dir) then
      print('ERROR: conflicting relation directions found for way ' .. way:id() .. 
            ' relation direction is ' .. result_direction .. ' superrelation direction is ' .. super_dir)
      result_direction = nil
    elseif result_direction == nil then
      result_direction = super_dir
    end

    result['route_direction'] = result_direction

    if role == 'forward' then
      result['route_forward'] = true
    elseif role == 'backward' then
      result['route_forward'] = false
    else
      result['route_forward'] = nil
    end

    add_extra_data(m)
  end

  return result
end

function Relations.process_way_refs(way, relations, result)
  local parsed_rel_list = {}
  local rel_id_list = relations:get_relations(way)
  for i, rel_id in ipairs(rel_id_list) do
    local rel = relations:relation(rel_id)
    parsed_rel_list[i] = Relations.parse_route_relation(rel, way, relations)
  end

  -- now process relations data
  local matched_refs = nil;
  if result.ref then
    local match_res = Relations.match_to_ref(parsed_rel_list, result.ref)

    function gen_ref(is_forward)
      local ref = ''
      for _, m in pairs(match_res) do
        if ref ~= '' then
          ref = ref .. '; '
        end

        local dir = m.dir.forward
        if is_forward == false then
          dir = m.dir.backward
        end

        if dir then
          ref = ref .. m.ref .. ' $' .. dir
        else
          ref = ref .. m.ref
        end
      end

      return ref
    end

    result.forward_ref = gen_ref(true)
    result.backward_ref = gen_ref(false)
  end
end

--local Guidance

-- Guidance: Default Mapping from roads to types/priorities
highway_classes = {
  motorway = road_priority_class.motorway,
  motorway_link = road_priority_class.motorway_link,
  trunk = road_priority_class.trunk,
  trunk_link = road_priority_class.trunk_link,
  primary = road_priority_class.primary,
  primary_link = road_priority_class.primary_link,
  secondary = road_priority_class.secondary,
  secondary_link = road_priority_class.secondary_link,
  tertiary = road_priority_class.tertiary,
  tertiary_link = road_priority_class.tertiary_link,
  unclassified = road_priority_class.unclassified,
  residential = road_priority_class.main_residential,
  service = road_priority_class.alley,
  living_street = road_priority_class.side_residential,
  track = road_priority_class.bike_path,
  path = road_priority_class.bike_path,
  footway = road_priority_class.foot_path,
  pedestrian = road_priority_class.foot_path,
  steps = road_priority_class.foot_path
}

default_highway_class = road_priority_class.connectivity;

motorway_types = Set {
  'motorway',
  'motorway_link',
  'trunk',
  'trunk_link'
}

-- these road types are set with a car in mind. For bicycle/walk we probably need different ones
road_types = Set {
  'motorway',
  'motorway_link',
  'trunk',
  'trunk_link',
  'primary',
  'primary_link',
  'secondary',
  'secondary_link',
  'tertiary',
  'tertiary_link',
  'unclassified',
  'residential',
  'living_street'
}

link_types = Set {
  'motorway_link',
  'trunk_link',
  'primary_link',
  'secondary_link',
  'tertiary_link'
}

-- returns forward,backward psv lane count
local function get_psv_counts(way,data)
  local psv_forward, psv_backward = Tags.get_forward_backward_by_key(way,data,'lanes:psv')
  if psv_forward then
    psv_forward = tonumber(psv_forward)
  end
  if psv_backward then
    psv_backward = tonumber(psv_backward)
  end
  return psv_forward or 0,
         psv_backward or 0
end

-- trims lane string with regard to supported lanes
local function process_lanes(turn_lanes,vehicle_lanes,first_count,second_count)
  if turn_lanes then
    if vehicle_lanes then
      return applyAccessTokens(turn_lanes,vehicle_lanes)
    elseif first_count ~= 0 or second_count ~= 0 then
      return trimLaneString(turn_lanes, first_count, second_count)
    else
      return turn_lanes
    end
  end
end

-- this is broken for left-sided driving. It needs to switch left and right in case of left-sided driving
function get_turn_lanes(way,data)
  local psv_fw, psv_bw = get_psv_counts(way,data)
  local turn_lanes_fw, turn_lanes_bw = Tags.get_forward_backward_by_key(way,data,'turn:lanes')
  local vehicle_lanes_fw, vehicle_lanes_bw = Tags.get_forward_backward_by_key(way,data,'vehicle:lanes')

  --note: backward lanes swap psv_bw and psv_fw
  return process_lanes(turn_lanes_fw,vehicle_lanes_fw,psv_bw,psv_fw) or turn_lanes,
         process_lanes(turn_lanes_bw,vehicle_lanes_bw,psv_fw,psv_bw) or turn_lanes
end

function set_classification (highway, result, input_way)
  if motorway_types[highway] then
    result.road_classification.motorway_class = true
  end
  if link_types[highway] then
    result.road_classification.link_class = true
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

  local lane_count = input_way:get_value_by_key("lanes")
  if lane_count then
    local lc = tonumber(lane_count)
    if lc ~= nil then
      result.road_classification.num_lanes = lc
    end
  else
    local total_count = 0
    local forward_count = input_way:get_value_by_key("lanes:forward")
    if forward_count then
      local fc = tonumber(forward_count)
      if fc ~= nil then
        total_count = fc
      end
    end
    local backward_count = input_way:get_value_by_key("lanes:backward")
    if backward_count then
      local bc = tonumber(backward_count)
      if bc ~= nil then
        total_count = total_count + bc
      end
    end
    if total_count ~= 0 then
      result.road_classification.num_lanes = total_count
    end
  end
end

--local Destination
function get_directional_tag(way, is_forward, tag)
  local v
  if is_forward then
    v = way:get_value_by_key(tag .. ':forward') or way:get_value_by_key(tag)
  else
    v = way:get_value_by_key(tag .. ':backward') or way:get_value_by_key(tag)
  end
  if v then
    return v.gsub(v, ';', ', ')
  end
end

-- Assemble destination as: "A59: Düsseldorf, Köln"
--          destination:ref  ^    ^  destination

function get_destination(way, is_forward)
  ref  = get_directional_tag(way, is_forward, 'destination:ref')
  dest = get_directional_tag(way, is_forward, 'destination')
  street = get_directional_tag(way, is_forward, 'destination:street')
  if ref and dest then
    return ref .. ': ' .. dest
  else
    return ref or dest or street or ''
  end
end

--local WayHandlers
WayHandlers = {}

-- set default mode
function WayHandlers.default_mode(profile,way,result,data)
  result.forward_mode = profile.default_mode
  result.backward_mode = profile.default_mode
end

-- handles name, including ref and pronunciation
function WayHandlers.names(profile,way,result,data)
  -- parse the remaining tags
  local name = way:get_value_by_key("name")
  local pronunciation = way:get_value_by_key("name:pronunciation")
  local ref = way:get_value_by_key("ref")
  local exits = way:get_value_by_key("junction:ref")

  -- Set the name that will be used for instructions
  if name then
    result.name = name
  end

  if ref then
    result.ref = canonicalizeStringList(ref, ";")
  end

  if pronunciation then
    result.pronunciation = pronunciation
  end

  if exits then
    result.exits = canonicalizeStringList(exits, ";")
  end
end

-- junctions
function WayHandlers.roundabouts(profile,way,result,data)
  local junction = way:get_value_by_key("junction");

  if junction == "roundabout" then
    result.roundabout = true
  end
end

-- determine if this way can be used as a start/end point for routing
function WayHandlers.startpoint(profile,way,result,data)
    result.is_startpoint = result.forward_mode == profile.default_mode or
                           result.backward_mode == profile.default_mode
end

-- handle turn lanes
function WayHandlers.turn_lanes(profile,way,result,data)
  local forward, backward = get_turn_lanes(way,data)

  if forward then
    result.turn_lanes_forward = forward
  end

  if backward then
    result.turn_lanes_backward = backward
  end
end

-- set the road classification based on guidance globals configuration
function WayHandlers.classification(profile,way,result,data)
  set_classification(data.highway,result,way)
end

-- handle destination tags
function WayHandlers.destinations(profile,way,result,data)
  if data.is_forward_oneway or data.is_reverse_oneway then
    local destination = get_destination(way, data.is_forward_oneway)
    result.destinations = canonicalizeStringList(destination, ",")
  end
end

-- handling ferries and piers
function WayHandlers.ferries(profile,way,result,data)
  local route = data.route
  if route then
    local route_speed = profile.route_speeds[route]
    if route_speed and route_speed > 0 then
     local duration  = way:get_value_by_key("duration")
     if duration and durationIsValid(duration) then
       result.duration = math.max(parseDuration(duration), 1 )
     end
     result.forward_mode = mode.ferry
     result.backward_mode = mode.ferry
     result.forward_speed = route_speed
     result.backward_speed = route_speed
    end
  end
end

-- handling movable bridges
function WayHandlers.movables(profile,way,result,data)
  local bridge = data.bridge
  if bridge then
    local bridge_speed = profile.bridge_speeds[bridge]
    if bridge_speed and bridge_speed > 0 then
      local capacity_car = way:get_value_by_key("capacity:car")
      if capacity_car ~= 0 then
        result.forward_mode = profile.default_mode
        result.backward_mode = profile.default_mode
        local duration  = way:get_value_by_key("duration")
        if duration and durationIsValid(duration) then
          result.duration = math.max( parseDuration(duration), 1 )
        else
          result.forward_speed = bridge_speed
          result.backward_speed = bridge_speed
        end
      end
    end
  end
end

-- service roads
function WayHandlers.service(profile,way,result,data)
  local service = way:get_value_by_key("service")
  if service then
    -- Set don't allow access to certain service roads
    if profile.service_tag_forbidden[service] then
      result.forward_mode = mode.inaccessible
      result.backward_mode = mode.inaccessible
      return false
    end
  end
end

-- check accessibility by traversing our access tag hierarchy
function WayHandlers.access(profile,way,result,data)
  data.forward_access, data.backward_access =
    Tags.get_forward_backward_by_set(way,data,profile.access_tags_hierarchy)

  -- only allow a subset of roads to be treated as restricted
  if profile.restricted_highway_whitelist[data.highway] then
      if profile.restricted_access_tag_list[data.forward_access] then
          result.forward_restricted = true
      end

      if profile.restricted_access_tag_list[data.backward_access] then
          result.backward_restricted = true
      end
  end

  -- blacklist access tags that aren't marked as restricted
  if profile.access_tag_blacklist[data.forward_access] and not result.forward_restricted then
    result.forward_mode = mode.inaccessible
  end

  if profile.access_tag_blacklist[data.backward_access] and not result.backward_restricted then
    result.backward_mode = mode.inaccessible
  end

  if result.forward_mode == mode.inaccessible and result.backward_mode == mode.inaccessible then
    return false
  end
end

-- handle speed (excluding maxspeed)
function WayHandlers.speed(profile,way,result,data)
  if result.forward_speed ~= -1 then
    return        -- abort if already set, eg. by a route
  end

  local key,value,speed = Tags.get_constant_by_key_value(way,profile.speeds)
 
  if speed then
    -- set speed by way type
    result.forward_speed = speed
    result.backward_speed = speed
  else
    -- Set the avg speed on ways that are marked accessible
    if profile.access_tag_whitelist[data.forward_access] then
      result.forward_speed = profile.default_speed
    elseif data.forward_access and not profile.access_tag_blacklist[data.forward_access] then
      result.forward_speed = profile.default_speed -- fallback to the avg speed if access tag is not blacklisted
    elseif not data.forward_access and data.backward_access then
       result.forward_mode = mode.inaccessible
    end
   
    if profile.access_tag_whitelist[data.backward_access] then
      result.backward_speed = profile.default_speed
    elseif data.backward_access and not profile.access_tag_blacklist[data.backward_access] then
      result.backward_speed = profile.default_speed -- fallback to the avg speed if access tag is not blacklisted
    elseif not data.backward_access and data.forward_access then
       result.backward_mode = mode.inaccessible
    end
  end

  if data.forward_access == "private" then
    result.forward_speed = profile.private_speed
  end

  if data.backward_access == "private" then
    result.backward_speed = profile.private_speed
  end

  if result.forward_speed == -1 and result.backward_speed == -1 and result.duration <= 0 then
    return false
  end
end

-- add class information
function WayHandlers.classes(profile,way,result,data)
    if not profile.classes then
        return
    end

    local allowed_classes = Set {}
    for k, v in pairs(profile.classes) do
        allowed_classes[v] = true
    end

    local forward_toll, backward_toll = Tags.get_forward_backward_by_key(way, data, "toll")
    local forward_route, backward_route = Tags.get_forward_backward_by_key(way, data, "route")
    local tunnel = way:get_value_by_key("tunnel")

    if allowed_classes["tunnel"] and tunnel and tunnel ~= "no" then
      result.forward_classes["tunnel"] = true
      result.backward_classes["tunnel"] = true
    end

    if allowed_classes["toll"] and forward_toll == "yes" then
        result.forward_classes["toll"] = true
    end
    if allowed_classes["toll"] and backward_toll == "yes" then
        result.backward_classes["toll"] = true
    end

    if allowed_classes["ferry"] and forward_route == "ferry" then
        result.forward_classes["ferry"] = true
    end
    if allowed_classes["ferry"] and backward_route == "ferry" then
        result.backward_classes["ferry"] = true
    end

    if allowed_classes["restricted"] and result.forward_restricted then
        result.forward_classes["restricted"] = true
    end
    if allowed_classes["restricted"] and result.backward_restricted then
        result.backward_classes["restricted"] = true
    end

    if allowed_classes["motorway"] and (data.highway == "motorway" or data.highway == "motorway_link") then
        result.forward_classes["motorway"] = true
        result.backward_classes["motorway"] = true
    end
end

-- scale speeds to get better average driving times
function WayHandlers.penalties(profile,way,result,data)
  if profile.properties.weight_name == 'routability' then
    if result.forward_speed > 0 then
      result.forward_rate = (result.forward_speed) / 3.6
    end
    if result.backward_speed > 0 then
      result.backward_rate = (result.backward_speed) / 3.6
    end
    if result.duration > 0 then
      result.weight = result.duration 
    end
  end
end


-- handle oneways tags
function WayHandlers.oneway(profile,way,result,data)
  if not profile.oneway_handling then
    return
  end

  local oneway
  if profile.oneway_handling == true then
    oneway = Tags.get_value_by_prefixed_sequence(way,profile.restrictions,'oneway') or way:get_value_by_key("oneway")
  elseif profile.oneway_handling == 'specific' then
    oneway = Tags.get_value_by_prefixed_sequence(way,profile.restrictions,'oneway')
  elseif profile.oneway_handling == 'conditional' then
    -- Following code assumes that `oneway` and `oneway:conditional` tags have opposite values and takes weakest (always `no`).
    -- So if we will have:
    -- oneway=yes, oneway:conditional=no @ (condition1)
    -- oneway=no, oneway:conditional=yes @ (condition2)
    -- condition1 will be always true and condition2 will be always false.
    if way:get_value_by_key("oneway:conditional") then
        oneway = "no"
    else
        oneway = Tags.get_value_by_prefixed_sequence(way,profile.restrictions,'oneway') or way:get_value_by_key("oneway")
    end
  end

  data.oneway = oneway

  if oneway == "-1" then
    data.is_reverse_oneway = true
    result.forward_mode = mode.inaccessible
  elseif oneway == "yes" or
         oneway == "1" or
         oneway == "true" then
    data.is_forward_oneway = true
    result.backward_mode = mode.inaccessible
  elseif profile.oneway_handling == true then
    local junction = way:get_value_by_key("junction")
    if data.highway == "motorway" or
       junction == "roundabout" or
       junction == "circular" then
      if oneway ~= "no" then
        -- implied oneway
        data.is_forward_oneway = true
        result.backward_mode = mode.inaccessible
      end
    end
  end
end

function WayHandlers.weights(profile,way,result,data)
  if profile.properties.weight_name == 'distance' then
    result.weight = -1
     -- set weight rates to 1 for the distance weight, edge weights are distance / rate
    if (result.forward_mode ~= mode.inaccessible and result.forward_speed > 0) then
       result.forward_rate = 1
    end
    if (result.backward_mode ~= mode.inaccessible and result.backward_speed > 0) then
       result.backward_rate = 1
    end
  end
end

-- Call a sequence of handlers, aborting in case a handler returns false. Example:
--
-- handlers = Sequence {
--   WayHandlers.tag_prefetch,
--   WayHandlers.default_mode,
--   WayHandlers.blocked_ways,
--   WayHandlers.access,
--   WayHandlers.speed,
--   WayHandlers.names
-- }
--
-- WayHandlers.run(handlers,way,result,data,profile)
--
-- Each method in the list will be called on the WayHandlers object.
-- All handlers must accept the parameteres (profile, way, result, data, relations) and return false
-- if the handler chain should be aborted.
-- To ensure the correct order of method calls, use a Sequence of handler names.

function WayHandlers.run(profile, way, result, data, handlers, relations)
  for i,handler in ipairs(handlers) do
    if handler(profile, way, result, data, relations) == false then
      return false
    end
  end
end

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
  -- Tuningid = lua, date = 2019-09-04
}

function setup()
  return {
    properties = {
      max_speed_for_map_matching      = 180/3.6, -- 180kmph -> m/s
      -- For routing based on duration, but weighted for preferring certain roads
      weight_name                     = 'routability',
      -- For shortest duration without penalties for accessibility
      -- weight_name                     = 'duration',
      -- For shortest distance without penalties for accessibility
      -- weight_name                     = 'distance',
      process_call_tagless_node      = false,
      u_turn_penalty                 = 20,
      continue_straight_at_waypoint  = true,
      use_turn_restrictions          = true,
      left_hand_driving              = false,
      traffic_light_penalty          = 2,
    },

    default_mode              = mode.driving,
    default_speed =  speed_profile.default,
    private_speed =  speed_profile.private,
    oneway_handling           = true,
    turn_penalty              = 7.5,
    cardinal_directions       = false,

    -- a list of suffixes to suppress in name change instructions. The suffixes also include common substrings of each other
    suffix_list = {
      'N', 'NE', 'E', 'SE', 'S', 'SW', 'W', 'NW', 'North', 'South', 'West', 'East', 'Nor', 'Sou', 'We', 'Ea'
    },

    barrier_whitelist = Set {
      'cattle_grid',
      'border_control',
      'checkpoint',
      'toll_booth',
      'sally_port',
      'gate',
      'lift_gate',
      'no',
      'entrance'
    },

    access_tag_whitelist = Set {
      'yes',
      'private',
      'motorcar',
      'motor_vehicle',
      'vehicle',
      'permissive',
      'designated',
      'destination'
    },

    access_tag_blacklist = Set {
      'no',
      'agricultural',
      'forestry',
      'emergency',
      'psv',
      'delivery'
    },

    restricted_access_tag_list = Set {
      'delivery',
      'destination'
    },

    access_tags_hierarchy = Sequence {
      'motorcar',
      'motor_vehicle',
      'vehicle',
      'access'
    },

    service_tag_forbidden = Set {
      'emergency_access'
    },

    restrictions = Sequence {
      'motorcar',
      'motor_vehicle',
      'vehicle'
    },

    classes = Sequence {
        'toll', 'motorway', 'ferry', 'restricted', 'tunnel'
    },

    speeds = Sequence {
      highway = speed_profile
    },

    restricted_highway_whitelist = Set {
      'motorway',
      'motorway_link',
      'trunk',
      'trunk_link',
      'primary',
      'primary_link',
      'secondary',
      'secondary_link',
      'tertiary',
      'tertiary_link',
      'unclassified',
      'residential',
      'living_street',
      'service'
    },

    route_speeds = {
      ferry = 5,
      shuttle_train =  speed_profile.shuttle_train
    },

    bridge_speeds = {
      movable =  speed_profile.movable
    },
    relation_types = Sequence {
      "route"
    },
  }
end

function process_node(profile, node, result, relations)
  -- parse access and barrier tags
  local access = find_access_tag(node, profile.access_tags_hierarchy)
  if access and access ~= "" then
    if profile.access_tag_blacklist[access] then
      result.barrier = true
    end
  else
    local barrier = node:get_value_by_key("barrier")
    if barrier and "" ~= barrier then
      --  make an exception for rising bollard barriers
      local bollard = node:get_value_by_key("bollard")
      local rising_bollard = bollard and "rising" == bollard

      if not profile.barrier_whitelist[barrier] and not rising_bollard then
        result.barrier = true
      end
    end
  end

  -- check if node is a traffic light
  local tag = node:get_value_by_key("highway")
  if "traffic_signals" == tag then
    result.traffic_lights = true
  end
end

function process_way(profile, way, result, relations)
  -- the intial filtering of ways based on presence of tags
  -- affects processing times significantly, because all ways
  -- have to be checked.
  -- to increase performance, prefetching and intial tag check
  -- is done in directly instead of via a handler.

  -- in general we should  try to abort as soon as
  -- possible if the way is not routable, to avoid doing
  -- unnecessary work. this implies we should check things that
  -- commonly forbids access early, and handle edge cases later.

  -- data table for storing intermediate values during processing
  local data = {
    -- prefetch tags
    impassable = way:get_value_by_key("impassable"),
    status = way:get_value_by_key("status"),
    railway = way:get_value_by_key('railway'),
    highway = way:get_value_by_key('highway'),
    bridge = way:get_value_by_key('bridge'),
    route = way:get_value_by_key('route'),
    oneway = way:get_value_by_key('oneway'),
    area = way:get_value_by_key('area')
  }

  -- perform an quick initial check and abort if the way is
  -- obviously not routable.
  -- highway or route tags must be in data table, bridge is optional
  if (not data.highway or data.highway == '') and data.bridge and data.bridge ~= ''then
    return
  end

  if (not data.highway or data.highway == '') and
  (not data.route or data.route == '') then
    return
  end

  if data.route and data.route == 'ferry' then
    local motor_vehicle = way:get_value_by_key("motor_vehicle")
    local motorcar = way:get_value_by_key("motorcar")
    if not ((motor_vehicle and motor_vehicle == "yes") or (motorcar and motorcar == "yes")) then
        return
    end
  end

  -- "route" key whitelist: ["road", "bus", "ferry"]
  if data.route and data.route ~= '' and not ('road' == data.route or 'bus' == data.route or 'ferry' == data.route) then
    return
  end

  if data.highway == 'track' or data.highway == 'path' or data.highway == 'footway' 
    or data.highway == 'pedestrian' or data.highway == 'steps' or data.highway == 'bus_stop' or data.highway == 'cycleway' then
    return
  end 

  if data.highway == 'construction' or data.railway == 'construction' then
    return
  end

  if data.impassable == 'yes' or data.status == 'impassable' then
      return
  end

  if data.area == 'yes' then
    return
  end

  handlers = Sequence {
    -- set the default mode for this profile. if can be changed later
    -- in case it turns we're e.g. on a ferry
    WayHandlers.default_mode,

    -- determine access status by checking our hierarchy of
    -- access tags, e.g: motorcar, motor_vehicle, vehicle
    WayHandlers.access,

    -- check whether forward/backward directions are routable
    WayHandlers.oneway,

    -- check a road's destination
    WayHandlers.destinations,

    -- check whether we're using a special transport mode
    WayHandlers.ferries,
    WayHandlers.movables,

    -- handle service road restrictions
    WayHandlers.service,

    -- compute speed taking into account way type, maxspeed tags, etc.
    WayHandlers.speed,
    WayHandlers.penalties,

    -- compute class labels
    WayHandlers.classes,

    -- handle turn lanes and road classification, used for guidance
    WayHandlers.turn_lanes,
    WayHandlers.classification,

    -- handle various other flags
    WayHandlers.roundabouts,
    WayHandlers.startpoint,

    -- set name, ref and pronunciation
    WayHandlers.names,

    -- set weight properties of the way
    WayHandlers.weights,
  }

  WayHandlers.run(profile, way, result, data, handlers, relations)

  if profile.cardinal_directions then
    Relations.process_way_refs(way, relations, result)
  end
end

function process_turn(profile, turn)
  -- Use a sigmoid function to return a penalty that maxes out at turn_penalty
  -- over the space of 0-180 degrees.  Values here were chosen by fitting
  -- the function to some turn penalty samples from real driving.
  local turn_penalty = 7.5
  local turn_bias =  1.075
  if turn.has_traffic_light then
    turn.weight = profile.properties.traffic_light_penalty
  end

  if turn.number_of_roads > 2 or turn.source_mode ~= turn.target_mode or turn.is_u_turn then
    if turn.angle>=0 then
      turn.weight = turn.weight + turn_penalty / (1 + 2.718 ^ - ((13 / turn_bias) * turn.angle/180 - 6.5*turn_bias))
    else
      turn.weight = turn.weight + turn_penalty / (1 + 2.718 ^  - ((13 * turn_bias) * - turn.angle/180 - 6.5/turn_bias))
    end
    if turn.is_u_turn then
      turn.weight = turn.weight + profile.properties.u_turn_penalty
    end
  end
  turn.duration = turn.weight
end

return {
  setup = setup,
  process_way = process_way,
  process_node = process_node,
  process_turn = process_turn
}
