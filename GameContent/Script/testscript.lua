function onInteract(direction) 
    log("TestNPC got an interaction!")
    log(tostring(1+5))
    log("My world position is " .. tostring(npc.worldPos.x) .. "x" .. tostring(npc.worldPos.y))
    log("Direction is " .. tostring(direction));
    log(tostring(math.random(1, 5)));
end
