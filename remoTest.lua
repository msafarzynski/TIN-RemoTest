--add to init.lua a line
--dofile(DATA_DIR.."remoTest.lua")


proto_remo = Proto ("remo","RemoTest Protocol")

local f_type = ProtoField.uint8("remo.type", "Type")
local f_command = ProtoField.uint8("remo.tool", "Tool")
local f_data = ProtoField.string("remo.data", "DATA", FT_STRING)


proto_remo.fields = {f_type, f_command, f_data}


function proto_remo.dissector (buf, pinfo, root)
	if buf:len() < 2 then return end
	local uiType = buf(0,1):uint()
	local uiCommand = buf(1,1):uint()
  
	if uiType > 1 then
		return
	end
	
	if uiCommand > 3 then
		return
	end
	
	local tType = {[0]='request', [1]='response'}	
	local tCommand = {[0]='iperf', [1]='ping', [2]='ethstats', [3]='stop'}
	
	local sType = tType[uiType]
	local sCommand = tCommand[uiCommand]
	local sData = buf(2):string()
	
	pinfo.cols.protocol = proto_remo.name
	pinfo.cols.info = string.format('%s %s %s', sType, sCommand, sData)
	
	local subtree = root:add(proto_remo, buf(), 'RemoTest Protocol Data')

	subtree:add(buf(0,1), string.format('Type: %d %s', iuType, sType))
	subtree:add(buf(1,1), string.format('Command: %d %s', iuCommand, sCommand))
	subtree:add(buf(2), string.format('Data: %s', sData))
end
 