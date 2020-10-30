

filename = "mpi_Ncore.slurm"
for i in range(1, 17):
    newfilename = "mpi_"+str(32+i*2)+"core.slurm"

    #file = open(filename, "rt")
    x = open(filename)
    s=x.read().replace("@", str(32+i*2)) 
    s=s.replace("*", str(16+i)) 
    x.close()

    x=open(newfilename,"w")
    x.write(s)
    x.close