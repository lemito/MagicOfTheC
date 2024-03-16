
if (argv[1] == '') { 
    const title = await question('Enter title: ') } 
else {
    const title = argv[1]
}

await $`mkdir ./src/${title}`
cd(`./src/${title}`)
await $`touch ${title}.c ${title}_lib.c  ${title}_lib.h BUILD`
echo(`Succes created files: ${title}.c ${title}_lib.c  ${title}_lib.h BUILD`)
