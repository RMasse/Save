/*TP4*/

/*1. Creation et manipulation de vues*/


/*1.1.*/
Create or Replace view circuit_pas_cher (nc,prix) as select nc, 
	prix from L2i_circuit where prix < 200;

Select * from circuit_pas_cher;

Select view_name from user_views;

Insert into circuit_pas_cher values (11,100);
//Insert into circuit_pas_cher values (5,100);

/*1.2.*/

Create table mon_circuit as select * from L2i_circuit;

//Select * from mon_circuit;

Create or Replace view circuit_pas_cher (nc,prix) as select nc, 
	prix from mon_circuit where prix < 200;


Insert into circuit_pas_cher values (13,300);

//Insert into circuit_pas_cher values (1,100);

/*1.3.*/

Create or Replace view circuit_pas_cher (nc,prix) as select nc, 
	prix from mon_circuit where prix < 200 with check option;


Update circuit_pas_cher set prix=300 where nc=1;

Update circuit_pas_cher set prix = 300 where nc = 2;

Insert into circuit_pas_cher values (14,300);

/*1.4.*/

Create table mon_ciretape as select * from l2i_ciretape;
Create table ma_ville as select * from l2i_ville;

Create or replace view circuit_anglais as select distinct nc from l2i_ciretape 
	where vilet in (Select nomv from l2i_ville where upper (pays) like 'ANGLETERRE');

Create or replace view circuit_anglais as select distinct nc from mon_ciretape 
	where vilet in (Select nomv from ma_ville where upper (pays) like 'ANGLETERRE');


/*2. Passation de privilèges sur les values*/

/*2.1.*/
Select * from /*idBD_binome*/.mon_circuit;
Select * from mahras.mon_circuit;

Grant Select on dcolaci.mon_circuit to mahras with grant option;

/*complément à faire pour la question 2.5*/
Grant Select on dcolaci.circuit_pas_cher to mahras with grant option;


/*2.2.*/

Select distinct table_name from all_tab_privs where grantor = 'DCOLACI';

/*2.3.*/

Insert into circuit_pas_cher values (130,100);

/*2.4.*/

Grant insert, delete, update on dcolaci.circuit_pas_cher to mahras with grant option;

/*Grant insert, delete, update on dcolaci.mon_circuit to mahras with grant option;
*/

Insert into mahras.circuit_pas_cher values (130,100);


/*2.5.*/

Revoke select on dcolaci.circuit_pas_cher from mahras;

