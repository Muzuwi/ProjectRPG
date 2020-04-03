function onInteract(direction) 
    log("TestNPC got an interaction!")
    log(tostring(1+5))
    log("My world position is " .. tostring(npc.worldPos.x) .. "x" .. tostring(npc.worldPos.y))
    log("Direction is " .. tostring(direction));
    log(tostring(math.random(1, 5)));
end

function onMove()
    log("I was moved!");
end

function onStep()
    log("I was stepped on!");
end

function onUpdate()
    --log("I was updated!");
end