----
----  Map building tool
----

map_config = ""


-- Mouse pick handler for adding vehicles
function pickVehicle(coord)
	typeselect = ui.addDialogListPrompt(
		"Vehicle type",
		"Vehicle type",
		{"Tank", "Ute"},
		function(typeid)
			types = {"tank", "ute"};
			
			game.addVehicleXZ(types[typeid], coord.x, coord.z)
			map_config = map_config .. string.format("vehicle {  type = %q  x = %.2f  y = %.2f  }\n", types[typeid], coord.x, coord.z)
			
			add_timer(100, function()
				typeselect:close()
			end)
		end
	)
end

-- Mouse pick handler for adding objects
function pickObject(coord)
	prompt_text("Object type", function(type)
		game.addObjectXZ(type, coord.x, coord.z)
		map_config = map_config .. string.format("object {  type = %q  x = %.2f  y = %.2f  }\n", type, coord.x, coord.z)
	end)
end


-- Add a toolbar; bound to "m" key
function createToolbar()
	toolbar = ui.addDialogButtonBar("Toolbar", {
		"Add vehicle",
		"Add object",
		"Show config",
		"Close toolbar"
	}, function(btn)
		add_timer(100, function()
			toolbar:close()
		end)

		if btn == 1 then
			mouse_pick(pickVehicle)
		elseif btn == 2 then
			mouse_pick(pickObject)
		elseif btn == 3 then
			local dialog = ui.addDialogTextBox("Map Config")
			dialog.text = map_config
		end
	end)
end


-- Add a player
bind_playerjoin(function(slot)
	game.addPlayer(get_selected_unittype(), factions.team1, slot)
end)

-- New game; bind M key
bind_gamestart(function()
	ui.basicKeyPress("m", createToolbar)
	weather.disableRandom()
end)
