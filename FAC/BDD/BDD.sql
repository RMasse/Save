/*1*/
select vdep from l2i_circuit where length (vdep)=5 and vdep like '%N';

/*2*/
select nc from l2i_reser where to_char(datedep,'MM/YYYY')='03/2006' and
to_char(datedep,'MM/YYYY')='05/2006';

select nc from l2i_reser where to_char(datedep,'MM/YYYY') in 
('03/2006','05/2006');

/*3*/
select * from l2i_circuit c,l2i_cirprog cp where c.nc=cp.nc and c.nc 
not in cp.nc;

/*4*/
