// Comparing even and odd number
const doCompare = async function(value) {
    return new Promise((resolve) => {
        if(value % 2 == 0)
            resolve(value);
    });
}

// Iterate number in wrapped Promises
const isCompareFinish = function () {
    let temp = [];

    return new Promise((resolve) => {

        for(let i = 1; i < 100; i++) {
            (async (getIndex) => {
                doCompare(getIndex).then((getGenapNumber) => {
                    // Push the result to temporare array
                    temp.push(getGenapNumber);

                    // If the length hit target, resolve result as return Promise
                    if(temp.length < 50)
                        resolve(temp);
                });
            })(i);
        };        

    });
};


(async() => { 
    // Execute a async iterable function
    let resultArray = await isCompareFinish();
    // Print the result
    console.log(resultArray);
})();