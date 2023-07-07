let len = Number(window.prompt("Length\n"));
let wid = Number(window.prompt("width\n"));
let StringLine = "";
for(let i = 0; i < wid; i++)
{
    for(let j = 0; j < len; j++)
    {
        if(j % 2 === i % 2)
            StringLine += '#';
        else
            StringLine += '-';
    }
    console.log(StringLine);
    StringLine = "";
}