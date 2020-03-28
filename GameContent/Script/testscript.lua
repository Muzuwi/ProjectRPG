function onInteract(direction) 
    log("TestNPC got an interaction!")
    log(tostring(1+5))
    log("My world position is " .. tostring(npc.worldPos.x) .. "x" .. tostring(npc.worldPos.y))
    log("Direction is " .. tostring(direction));
    a = {};
    for i = 1, 10 do
        a[i] = i
    end
    for i, v in pairs(a) do
        log(tostring(v));
    end
end
