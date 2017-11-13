exo1
1/
select vilet from l2i_ciretape where nc 
in (select nc from l2i_reser where nomc='GrosseBaf');
2/
select distinct nc from l2i_ciretape where vilet 
in (select nomv from l2i_ville where pays='Irlande');
3/
select distinct nomv from l2i_monument having count(nomm)>1 group by nomv;
4/
select nc,vdep,varr from l2i_circuit where nc in (select nc from 
l2i_cirprog where to_char(DATEDEP,'DD/MM/YYYY')='17/04/2006' and nblibr>10);
5/
select nomm from l2i_monument where nomv in (select vilet from l2i_ciretape where nc in
(select nc from l2i_reser where lower(nomc)='asterix'));
6/
select distinct nc,datedep from l2i_cirprog where nc in (select nc from l2i_ciretape
where vilet in (select nomv from l2i_ville where lower(pays)='angleterre'));
7/
select r.nc,nomc from l2i_reser r,l2i_circuit ci where r.nc=ci.nc order by nc;


exo2
1/
select count(distinct nomm) as "nb monument" from l2i_monument mo,l2i_ville v 
where mo.nomv=v.nomv and upper(v.pays)='FRANCE';
2/
select avg(prix) as "prix moyen" from l2i_circuit;
3/
select sum(nbres),nomc from l2i_reser group by nomc;
4/
select * from l2i_circuit where prix=(select max(prix) from l2i_circuit);
5/
select distinct nomv from l2i_monument group by nomv having count(nomm)>1;
6/
select sum(count(nomm)) "nb monument" from l2i_monument group by nomv having 
nomv in (select c.vilet from l2i_reser r, l2i_ciretape c where r.nc=c.nc and lower(
r.nomc)='donald');
7/
select nomv, count(nomm) from l2i_monument group by nomv having nomv in (select c.vilet 
from l2i_reser r, l2i_ciretape c where r.nc=c.nc and lower(r.nomc)='donald');
8/
select nomc, sum(nbres * prix) from l2i_reser r, l2i_circuit c where r.nc=c.nc group by
nomc;
9/
select max(sum(nbres * prix)) from l2i_reser r, l2i_circuit c where r.nc=c.nc group by
nomc;
10/
select nomc,sum(nbres * prix) from l2i_reser r, l2i_circuit c where r.nc=c.nc 
group by nomc having sum(nbres * prix)=(select max(sum(nbres * prix)) from l2i_reser r, 
l2i_circuit c where r.nc=c.nc group by nomc);
11/
select nomc,count(*) from l2i_reser r,l2i_monument m, l2i_ciretape c where 
r.nc=c.nc and c.vilet=m.nomv group by nomc;
