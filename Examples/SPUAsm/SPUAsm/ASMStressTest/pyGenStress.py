numIt = int(input("Entur number of iterations: "))

outString = "; Stress test\n"

for i in range(numIt):
    outString = outString + "push " + str(i) + "\nout\n" + "pop\n"

outFile = open("stress.spus", "w")
outFile.write(outString)
outFile.close()
