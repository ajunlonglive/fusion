
let s = "abacaba", temp = [], skip = -1, char = "";

for(let index = 0; index < s.length; index++) {
    if(index > skip) {
        if((temp.includes(s[index]) && s[index] != s[index+1]) || char.length) {
            char += s[index];

            if(!temp.includes(char)) {
                temp.push(char);
                char = "";
            }
            skip++;
            continue;
        }

        if(char.length)
            temp.push(char)

        temp.push(s[index])
        char = "";
    }
}


let last = temp.length - 1;

if(char.length > 1 || temp[last] == char)
    temp.push(char)
else
    temp[last] = (temp[last] + char)

console.log(temp);