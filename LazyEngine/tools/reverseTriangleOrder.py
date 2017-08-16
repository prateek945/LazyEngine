def swapOrder(buffer):
	for i,val in enumerate(buffer):
		if(i%3 == 0):
			temp = buffer[i]
			buffer[i] = buffer[i+1]
			buffer[i+1] = temp
	return buffer
		
def main():
	positionfile = open("C:\LazyEngine\LazyEngine\LazyEngine\Meshes\IndexBuffer\Sphere.ib",'r')
	lines = positionfile.readlines()
	index_buffer = []
	index_count = int(lines[0].strip('\n').strip('\r'))
	for i,line in enumerate(lines):
		if(i!=0):
			nums = line.split(" ")
			#print nums
			index_buffer.append(int(nums[0]))
			index_buffer.append(int(nums[1]))
			index_buffer.append(int(nums[2]))
	index_buffer = swapOrder(index_buffer)
	positionfile.close()
	positionfile = open("C:\LazyEngine\LazyEngine\LazyEngine\Meshes\IndexBuffer\Sphere.ib",'w')
	positionfile.write(str(index_count)+"\n")
	for i in range(index_count):
		positionfile.write(str(index_buffer[i*3])+" ")
		positionfile.write(str(index_buffer[i*3+1])+" ")
		positionfile.write(str(index_buffer[i*3+2])+"\n")
	positionfile.close()
if __name__ == "__main__":
	main()
	
