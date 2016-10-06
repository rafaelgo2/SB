DESCRICAO DOS TESTES:

teste1.a calcula o fatorial de um inteiro positivo. Como os 
	registradores da Wombat2 so suportam inteiros de 16bits,
	a maior entrada aceita eh 8 (pois 8! > 2^16-1). A
	primeira entrada recebida eh a quantidade N de fatoriais
	a serem serem computados, seguida de N inteiros que
	respeitem as restricoes citadas. Caso qualquer entrada
	recebida seja invalida, o programa espera por outra.

teste2.a calcula o resultado de uma equacao de segundo grau
	da forma Ax^2+Bx+C. A tres primeiras entradas devem
	especificar A, B e C, e as entradas seguintes, enquanto
	nao nulas, indicam valores de x. Todos os resultados
	calculados sao armazenados na pilha e, apos a ultima
	entrada, a pilha (que a partir deste momento eh
	rebaixada a lista) comeca ser percorrida e seus itens
	sao ordenados usando o algoritmo BUBBLE SORT. Quando a
	lista estiver ordenada, seus itens sao impressos em
	ordem crescente.
