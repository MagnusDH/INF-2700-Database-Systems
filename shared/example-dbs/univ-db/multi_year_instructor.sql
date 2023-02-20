-- These queries show how you can solve the same problem in different ways.
-- If you are in a sqlite3 shell with 'sqlite3 univ_db.sqlite3',
-- you can run the queries with '.read multi_year_instructor.sql'.
-- You can also run these directly from a (bash) shell with
-- 'sqlite3 univ_db.sqlite3 < multi_year_instructor.sql',

.print "\033[1m==different years==\033[m"

.print "use join"
select distinct t1.ID, t1.year, t2.year
from   teaches as t1, teaches as t2
where  t1.ID = t2.ID and t1.year < t2.year;

.print "\nuse having"
select ID         -- notice distinct
from   teaches
group by ID
having count(distinct year) > 1;

.print "\n\033[1m==both 2009 and 2010==\033[m"

.print "use join"
select distinct t1.ID
from   teaches as t1, teaches as t2
where  t1.ID = t2.ID and t1.year = 2009 and t2.year = 2010;

.print "\nuse intersect"
select id from teaches where year = 2009
intersect
select id from teaches where year = 2010;

.print "\nuse exists"
select distinct id from teaches t
where  exists
       (select id from teaches where id = t.id and year = 2009)
       and exists
       (select id from teaches where id = t.id and year = 2010);

.print "\njoin as intersect"
select distinct *
from   (select id from teaches where year = 2010)
       natural join
       (select id from teaches where year = 2009);

.print "\nuse subquery"
select id
from   teaches
where  year = 2010
       and id in (select id from teaches where year = 2009);

.print "\nuse correlated subquery"
select distinct id
from   teaches t
where  year = 2009 and exists
       (select *
        from   teaches
        where  id = t.id and year = 2010);
