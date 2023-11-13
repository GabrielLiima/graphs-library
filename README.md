# Trabalho 1
Este primeiro trabalho de Teoria dos Grafos consiste em uma biblioteca para manipular grafos, capaz de representar grafos, e implementar um conjunto de algoritmos em grafos.

Autor: Gabriel Lima

# Compilação
Para compilar o programa no linux, primeiro navegue até a pasta raiz do programa. Utilize

	cd caminho_para_diretorio/teoria_grafos_trabalho_1

para abrir a pasta no terminal. Agora, basta executar

	make all
	
para compilar todos os arquivos necessários.

Além disso, um arquivo texto poderá ser utilizado para ler um grafo. O formato do grafo no arquivo é o seguinte: a primeira linha informa o número de vértices do grafo, e cada linha subsequente informa as arestas.

Após compilar os arquivos, o executável <b>main</b> será criado dentro da pasta <b>bin</b>. Assim, para rodar o programa, digite no terminal

	bin/main arquivo_entrada.txt
	
que o programa será executado.