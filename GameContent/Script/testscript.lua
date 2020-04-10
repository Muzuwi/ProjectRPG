--dirs = {0, 1, 3, 2}
n = 0
hatesMe = 0

function firstTalk()
    dialog:say("Hello, my name is Test!");

    dialog:ask("Say, do you like jazz?", 
        {"Yes", "Nope", "Yup"}
        );

    if dialog.choice == 0 or dialog.choice == 2 then
        hatesMe = 2;
        dialog:say("Hell yeah brother!"); 
    else
        hatesMe = 1;
        dialog:say("Shame on you!");
        dialog:ask("Or do you want to redeem yourself?", {"Yeah", "Nope"});

        if dialog.choice == 0 then
            sound:playSound("sheep7");
            dialog:say("You are redeemed!");
            hatesMe = 0;
        else
            dialog:say("Begone then!");
        end
    end
end


function onInteract(direction)
    log("TestNPC got an interaction!")
    log("My world position is " .. tostring(npc.worldPos.x) .. "x" .. tostring(npc.worldPos.y))
    log("Random number for you: " .. tostring(math.random(1, 5)));
    log("I've survived " .. tostring(n) .. " update ticks!");
    npc.direction = direction;

    if hatesMe == 0 then
        firstTalk()
    else
        if hatesMe == 1 then
            dialog:say("You're not a jazz fan!");
        elseif hatesMe == 2 then
            dialog:say("Ah, my favourite Jazz friend!");
        end
    end

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