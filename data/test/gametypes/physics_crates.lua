----
----  Physics test - 100 crates
----
debug_framerate(true)


bind_gamestart(function()
	-- Make some crates!
	for i = 0, 50, 1 do
		game.addPickupRand("ammo_current");
	end
	
	-- The game doesn't last long
	add_interval(1000 * 20, function()
		game_over(1)
	end)
end)
