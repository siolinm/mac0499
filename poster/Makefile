AUXFILES=main.aux main.toc main.loc main.bbl main.blg main.lot main.log main.pdf main.out main-blx.bib main.lof main.dvi main.run.xml main.nav main.snm tex_build.log

.PHONY: clear tex

all: main.pdf

tex: main.pdf

clear:
	rm ${AUXFILES}

main.pdf: main.tex beamerthemeposter-exemplo.sty
	pdflatex main.tex
	pdflatex main.tex
	pdflatex main.tex
