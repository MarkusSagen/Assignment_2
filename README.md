# Assignment_2
Assignment 2 for the course IOOPM  HT 2018  

 <br/>
Detta program bygger en virituel butik där användaren kan sätta in egna varor i butiken, lägga till eller ta bort varor och även skapa olika kundvangar för att handla saker från sortimentet.  <br/>
Programmet öppnas enklast med något av kommandona nedan i terminalen med den medföljande makefilen. <br/>
Den virituella butiken har 14 val att välja på, som visas på terminalens fönster när programmet körs.  <br/>
Skriv in någon av de 14 valen nummer 1-14.    <br/>
För att bekräfta ett val, tryck på enterknappen efter du skrivit in vad vill göra för val.    <br/>
<br/>
Mer information om funktionernas struktur och uppbyggnad står det att läsa både i dokumentationen för funktionerna och i den bifogade doxygen dokumentationen.  
<br/>   
<br/>
För att läsa doxygen dokumentation, packa först upp zip filen "doxy" <br/>
Navigera sedan till mappen "html" och klicka på filen "index.html" för att se dokumentation av programmet </br>

För mer information om programmets uppbyggnad och kursen:  <br/> 
http://wrigstad.com/ioopm18/assignments/assignment2.html  
<br/> 
<br/>
<br/>
Vi anntar att den input som ges av användare är kompatibel med de jämförelse funktioner som ges.  <br/> 
Misslyckande att göra detta kan resultera i fel av programmet.  <br/> 
Vi förutsätter att användare tar del av dokumentationen.   <br/> 
Dock bör programmet skydda mot felaktig användning (Exempelvis: försöka ta bort element som inte finns)  <br/> 
<br/>
<br/>
<br/>
<br/>

##### För att bygga programmet - I terminalen, navigera till mappen: 
##### Skriv in något av följande i terminalen  
<br/>

Fulla namn   | Kort kommando | Förlaring
------------ | --------------|----------------------------------
|`make` |                       | För att **_bygga_** programmet |
| `make run` |  `make r`        | För att bygga och **_köra_ _programmet_**  |
| `make test` | `make memtest`  | För att bygga och **_köra_ _tester_ i  `valgrind`**  |
| `make test_r` | `make t`      | För att **köra testerna _vanligt_**  |
|   ---           |      ---    | ---                    |
| `make clean` | `make c`       | För att **städa enkelt**  |
|`make force_clean` | `make fc` | För att **städa effektivt**            |
|`make clean_force` | `make cf` | För att **städa effektivt**   |


  <br/>
  <br/>
  <br/>
  <br/>
  ## Dokumentation:
  När programmet väl är startat: Har du 14 val, var av en av dessa val (undo), inte funkar. <br/>
  <br/>
  <br/>
  
  	MENU
	――――――――
1	Add Merchandise
2	List Merchandise
3	Remove Merchandise
4	Edit Merchandise
5	Show Stock
6	Replenish
7	Create Cart
8	Remove Cart
9	Add To Cart
10	Remove From Cart
11	Calcute Cost
12	Checkout
13	Undo
14	Quit
  
  <br>
  <br/>
  
  För att göra något i programmet måste "varor" först läggas till som påtänkta varor genom att skriva in <b> 1 </b> och tryck enter: <br/>
  Ange namn:  <br/>
  Beskrivning:  <br/>
  Pris:   <br/>
  Tryck enter för att bekräfta varje val
  <br/>
  <br/>
  <br>
  
  För att varor ska kunna köpas an en användare behöver de läggas in i lager på en lagerplats och ett saldo:
  För att lägga in varor i butiken så tar vi namnet från en av de varor som ligger som påtänkt vara och skriver in <b> 6 </b> och tryck enter: <br/>
  Ange varans namn: <br/>
  Ange plats: <br/>
  Ange antal: <br/>
  Tryck enter för att bekräfta varje val
  <br/>
  <br/>
  <br>
  
  Nu finns de varor att handla. Men innan vi kan köpa dem behöver vi skapa en varukorg genom att skriva <b> 7 </b> och tryck enter: <br/>
  Tryck enter för att bekräfta valet <br/>
  En vagn med index "1" har nu skapats. <br/>
  <br/>
  <br/>
  <br>
  
  För att lägga till varor i vagnen, skriv in <b> 9 </b> och tryck enter: <br/>
  Ange index på vagnen som heltal: <br/>
  Ange namn på vara att lägga till: <br/>
  Ange antal av varan: <br/>
  Tryck enter för att bekräfta varje val
  <br/>
  <br/>
  <br>
  
  Vi kan nu beräkna pris på vad alla varorna i vår vagn kostar <b> 11 </b> och tryck enter: <br/>
  Ta bort en vara <b> 10 </b> 
  <br/>
  <br/>
  <br>
  
  För att ta köpa samtilga varor i vagnen skriv, skriv in <b> 12 </b> och tryck enter:<br/>
  Ange index på vagnen som heltal: <br/>
  Tryck enter för att bekräfta varje val
  <br/>
  <br/>
  <br>
  
  Du har nu köpt varor från butiken!
  

           
     

<br/>        
<br/>   
<br/>               
<br/>        
<br/>        
<br/>    
<br/>  
<br/>        
<br/>    
<br/> 
            
      

[Christian Wiren](mailto:christian.wiren.6049@student.uu.se)  
[Markus Johnson](mailto:markus.johnson.93@gmail.com)








