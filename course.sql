-- Active: 1652265351695@@host.docker.internal@3306@proj


DELETE FROM course

CREATE TABLE course(  
    -- id int NOT NULL PRIMARY KEY AUTO_INCREMENT COMMENT 'Primary Key',
    -- create_time DATETIME COMMENT 'Create Time',
    department VARCHAR(50),
    course VARCHAR(20),
    course_title VARCHAR(50),
    semester VARCHAR(20),
    course_id INT,
    faculty_name VARCHAR(50),
    faculty_uni VARCHAR(20),
    prereq1 VARCHAR(20),
    prereq2 VARCHAR(20),
    prereq3 VARCHAR(20),
    UNIQUE KEY (semester, course)
) COMMENT 'raw course table';

# INSERT
INSERT INTO course (department,course,course_title,semester,course_id,faculty_name,faculty_uni,prereq1,prereq2,prereq3)
VALUES
    ('CS','cs4156','Software','2022Fall','1111','Abby Smith','as1111','cs3000',NULL,NULL),
    ('CS','cs4111','Database','2022Fall','1112','Bob Smith','bs1111','cs3000','cs3200',NULL),
    ('CS','cs4118','Operating System','2022Fall','1113','Cathy Smith','cs1111','cs3000','cs3200','cs3500'),
    ('DS','ds4777','Core Data Science','2022Spring','0111','David Smith','ds1111',NULL,NULL,NULL);


-- check : cannot use unique key directly
-- select * from course
-- where course = 'cs4156' and semester = '2022Fall'


-- duplicate INSERT; success if cannot insert
-- INSERT INTO course (department,course,course_title,semester,course_id,faculty_name,faculty_uni,prereq1,prereq2,prereq3)
-- VALUES
--     ('CS','cs4156','Software','2022Fall','1111','Abby Smith','as1111','cs3000',NULL,NULL);

# UPDATE
-- NOTE : this must use a if duplicate name ?
-- UPDATE course as a
-- SET a.course_title = 'Adv Software'
-- WHERE a.course = 'cs4156'

