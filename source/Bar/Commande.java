import java.rmi.Naming;
import java.rmi.RemoteException;
import java.util.Vector;

import java.net.InetSocketAddress;
import java.io.IOException;
import static java.lang.Integer.parseInt;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import static java.lang.Integer.parseInt;

public class Commande {
    
    public static void main(String[] args) throws SocketException, IOException {

        DatagramSocket socket;
DatagramPacket packet;


try {
    // création d'une socket liée au port 7777
   socket = new DatagramSocket(null);
socket.setReuseAddress(true);
socket.bind(new InetSocketAddress(7777));
} catch (SocketException ex) {
    System.err.println("Erreur lors de la création de la socket : " + ex.getMessage());
    return;


}



// tableau de 15 octets qui contiendra les données reçues
byte[] data = new byte[50];

// création d'un paquet en utilisant le tableau d'octets
packet = new DatagramPacket(data, data.length);


        
        

        
        try {
            // Récupération de la référence distante du serveur
            IBiere serveur = (IBiere) Naming.lookup("rmi://10.1.13.52/DedeLaChope");

            // Exemple d'utilisation de la méthode listeBlondes()
            System.out.println(args[0]);
            Vector<Biere> bieres = null;
            
            if(args[0].equals("biere")){
                bieres = serveur.listeAmbrees();
                System.out.println("Liste des bières ambrees :");
            
                for (int i = 0; i < bieres.size(); i++) {
                Biere biere = bieres.get(i);
                System.out.println((i+1) + " - " + biere.getNom() + " ["  + biere.getDegre() + "]");
            }
            }
            else{
                bieres = serveur.listeBlondes();
                System.out.println("Liste des bières bieres :");
            
                for (int i = 0; i < bieres.size(); i++) {
                Biere biere = bieres.get(i);
                System.out.println((i+1) + " - " + biere.getNom() + " ["  + biere.getDegre() + "]");
            }
            }

        socket.receive(packet);
        String chaine = new String(packet.getData(), 0,packet.getLength());
        
        int commande = parseInt(chaine);
        
        Biere biere = bieres.get(commande-1);
        
        
         // Exemple d'utilisation de la méthode acheterBiere()
            Biere achat = serveur.acheterBiere(biere.getNom());
            if (achat != null) {
                System.out.println("Bière achetée : " + achat.getNom());
            } else {
                System.out.println("La bière n'existe pas");
            }
        String reponse = achat.getNom();
        packet.setData(reponse.getBytes());
        packet.setLength(reponse.length());
        socket.send(packet);

        socket.receive(packet);
        chaine = new String(packet.getData(), 0, packet.getLength());
   
        
        reponse = Integer.toString(achat.getDegre());
        packet.setData(reponse.getBytes());
        packet.setLength(reponse.length());
        socket.send(packet);

       

        

        // attente de la réception d'un paquet. Le paquet reçu est placé dans packet et ses données dans data.
        
        socket.close();
        return;
            

           

        } catch (Exception ex) {
            System.err.println("Erreur : " + ex.getMessage());
            ex.printStackTrace();
        }// attente de la réception d'un paquet. Le paquet reçu est placé dans packet et ses données dans data.
        
    }

}