--dirs = {0, 1, 3, 2}
n = 0

function onInteract(direction)
    log("TestNPC got an interaction!")
    log("My world position is " .. tostring(npc.worldPos.x) .. "x" .. tostring(npc.worldPos.y))
    log("Random number for you: " .. tostring(math.random(1, 5)));
    log("I've survived " .. tostring(n) .. " update ticks!");
    npc.direction = direction;
end

function onMove()
    --log("I was moved!");
end

function onStep()
    --log("I was stepped on!");
end

function onUpdate()
    --log("I was updated!");
    --if npc.moving == false then
    --    npc:move(dirs[(n%4) + 1])
    --end
    n = n+1
end