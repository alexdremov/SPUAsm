from os import walk


dirs = [
"SoftProcessorUnit/"
]



def fetchTree(dirs, current):
    for (dirpath, _, _) in walk(current):
        dirs.append(dirpath)

finalPaths = []

for path in dirs:
    fetchTree(finalPaths, path)


finalPaths = "\n".join(finalPaths)

templateFile = open("CMakeLists.template.txt", "r")
template = templateFile.read()
templateFile.close()

template = template.replace("{{include_dirs}}", finalPaths)

outFile = open("CMakeLists.txt", "w")
outFile.write(template)
outFile.close()
