
var title = ''
if (argv[1] == '') { 
    title = await question('Enter title: ') } 
else {
    title = argv[1]
}

await $`mkdir ./src/${title}`
cd(`./src/${title}`)
await $`touch ${title}.c ${title}_lib.c  ${title}_lib.h BUILD`
echo(`Succes created files: ${title}.c ${title}_lib.c  ${title}_lib.h BUILD`)
