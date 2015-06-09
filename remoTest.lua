--add to init.lua a line
--dofile(DATA_DIR.."remoTest.lua")

do

local proto_remo = Proto ("remo","RemoTest Protocol")

funtion proto_remo.init()
end

local f_type = ProtoField.uint8("remo.type", "Type")
local f_size = ProtoField.uint32("remo.size", "Size")
local f_data = ProtoField.string("remo.data", "DATA")


proto_remo.fields = {f_type, f_command, f_data}


function proto_remo.dissector (buf, pinfo, root)

	if buf:len() < 1 then return end
	local uiType = buf(0,1):uint()
	local size = 0:uint()
	local data = "":string()
  
	if uiType > 4 then
		return
	end
	
	local tType = {[0]='STOP', [1]='START_SCRIPT', [2]='SCRIPT', [3]='START_RESPONSE', [4]='RESPONSE'}
	
	local sType = tType[uiType]


	if uiType != 0 then
		size = buf(1,4):uint()
		data = buf(5):string()
	end
	
	pinfo.cols.protocol = proto_remo.name
	pinfo.cols.info = string.format('%s %s %s', sType, size, data)
	
	local subtree = root:add(proto_remo, buf(), 'RemoTest Protocol Data')

	subtree:add(buf(0,1), string.format('Type: %d %s', iuType, sType))
	subtree:add(buf(1,1), string.format('Command: %d', size))
	subtree:add(buf(2), string.format('Data: %s', data))
end
	local tcp_dissector_table = DissectorTable.get("tcp.port")
    	original_http_dissector = tcp_dissector_table:get_dissector(3491)
    	tcp_dissector_table:add(3491, protoRemo)
end
 
