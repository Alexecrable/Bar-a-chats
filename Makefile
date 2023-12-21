all : client bar Fournisseur



	

bar :
	gcc -o bar.out source/Bar/Barman.c
	
	javac source/Bar/Biere.java source/Bar/IBiere.java source/Bar/Commande.java


client :
	gcc -o client.out source/Client/client.c

Fournisseur :
	
	javac source/Fournisseur/Biere.java source/Fournisseur/Fournisseur.java source/Fournisseur/IBiere.java

clean :
	rm bar.out 
	rm client.out
	rm source/Bar/Biere.class
	rm source/Bar/IBiere.class
	rm source/Bar/Commande.class
	rm source/Fournisseur/Biere.class
	rm source/Fournisseur/IBiere.class
	rm source/Fournisseur/Fournisseur.class