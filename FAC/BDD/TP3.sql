/*exo1*/
/*1*/
create table Etudiant(net number(3) primary key,nom varchar(20),age number(2));
/*2*/
insert into Etudiant values (1,'Lopez',22);
insert into Etudiant(age,nom,net) values (25,'Jean',3);
insert into Etudiant values (5,null,null);
insert into Etudiant(net,nom) values (8,'Marie');
/*3*/
update Etudiant set age=26 where upper(nom) like 'LO%';
delete from Etudiant where nom is null;
/*4*/
alter table Etudiant add constraint etudiant_age_ck check (age>=18);
/*pour voir le nom des contraintes*/
select constraint_name owner from user_constraints;
/*5*/
alter table Etudiant add (adresse varchar(30));
insert into Etudiant values (13,'Lola',26,'Strasbourg');
insert into Etudiant values (14,'Louis',26,'Colmar');
insert into Etudiant values (23,null,null,null);
insert into Etudiant values (25,'Lise',30,null);
insert into Etudiant values (26,'Paul',15,'Strasbourg');

/*exo2*/
/*1*/
create table Cout(age number(2) primary key,tarif number(1), constraint 
cout_tarif_ck check (tarif between 1 and 3));
/*2*/
insert into Cout values (18,1);
insert into Cout values (18,5);
insert into Cout values (25,2);
/*3*/
alter table Etudiant add constraint etudiant_age_fk foreign key (age) 
references Cout(age);





