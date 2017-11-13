select nomc from l2i_reser order by nomc;
select nc,prix from l2i_circuit order by prix desc;
select vdep,nc from l2i_circuit;
select nomc from l2i_reser where to_char(datedep,'yyyy')=2005;
select nomc from l2i_reser where to_char(datedep,'mm-yyyy')='04-2006';
select nomc from l2i_reser where to_char(datedep,'yyyy')=to_char(sysdate-2,'yyyy');
select nomc from l2i_reser where to_char(datedep,'mm') in ('05','09');
select * from l2i_circuit where nc in (select nc from l2i_ciretape where upper(vilet) not in('LONDRES','AMSTERDAM'));
select nr,nc from l2i_reser where to_char(datedep,'mm') between '04' and '09';
select nr,datedep,nbres from l2i_reser where upper(nomc)='PICSOU';
select * from l2i_ville where upper(nomv) like '%PORT%';

