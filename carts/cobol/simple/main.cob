      *> simple COBOL cart for null0 (experimental)
       IDENTIFICATION DIVISION.
       PROGRAM-ID. simple.
       DATA DIVISION.
       WORKING-STORAGE SECTION.
       COPY null0.
       PROCEDURE DIVISION.
           CALL "clear" USING BY VALUE BLUE
           CALL "draw_circle" USING BY VALUE 100 100 50 RED
           STOP RUN.
