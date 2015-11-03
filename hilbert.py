def hilbert(n):
	matrix = []
	for i in range(n):
		matrix.append([])
		for j in range(n):
			matrix[i].append(1./(1 + i + j))
	return matrix

def print_matrix(A):
	for i in range(len(A)):
		for j in range(len(A[i])):
			print A[i][j],
		print
	print

print_matrix(hilbert(2))
print_matrix(hilbert(3))
print_matrix(hilbert(6))
