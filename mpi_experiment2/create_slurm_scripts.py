

filename = "mpi_Ncore.slurm"
for i in range(2, 33):
    newfilename = "mpi_"+str(i)+"core.slurm"

    #file = open(filename, "rt")
    x = open(filename)
    s=x.read().replace("@", str(i)) 
    x.close()

    x=open(newfilename,"w")
    x.write(s)
    x.close