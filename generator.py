import os
import re

# --- Configuration ---
SRC_DIR = "codes"
OUTPUT_TEX = "notebook_generated.tex"

LATEX_HEADER = r"""\documentclass[10pt, landscape, twocolumn, a4paper, notitlepage]{article}
\usepackage{xeCJK}
\setCJKmainfont{IPAMincho}
\setCJKsansfont{IPAGothic}
\setCJKmonofont{IPAGothic}
\usepackage{hyperref}
\usepackage[spanish, activeacute]{babel}
\usepackage{fancyhdr}
\usepackage{lastpage}
\usepackage{listings}
\usepackage{amssymb}
\usepackage{svnkw}
\usepackage{rotating}
\usepackage{amsmath}

%%% Márgenes
\setlength{\columnsep}{0.25in}    % default=10pt
\setlength{\columnseprule}{0.5pt}    % default=0pt (no line)

\addtolength{\textheight}{2.35in}
\addtolength{\topmargin}{-0.9in}     % ~ -0.5 del incremento anterior

\addtolength{\textwidth}{1.1in}
\addtolength{\oddsidemargin}{-0.60in} % -0.5 del incremento anterior
\setlength{\headwidth}{\textwidth}
\addtolength{\headwidth}{0.1in}

\setlength{\headsep}{0.08in}
\setlength{\parskip}{0in}
\setlength{\headheight}{15pt}
\setlength{\parindent}{0mm}

%%% Encabezado y pie de página
\pagestyle{fancy}
\fancyhead[LO]{\leftmark\ -\ \rightmark}
%\fancyhead[C]{\textbf{AJI-UBA}} el real...
\fancyhead[RO]{\textbf{(FFT) Final Fourier Tactics} - rev __DATE__ - P\'agina \thepage\ de \pageref{LastPage}\ \begin{rotate}{270}\hspace{.8em}\underline{\textbf{Universidad Cat\'olica Boliviana - UCB }\hspace{4.1in}\ }\end{rotate}}
\fancyfoot{}
\fancyfoot[RO]{\begin{rotate}{270}\hspace{-10em}\textbf{Page \thepage\ of \pageref{LastPage}}\end{rotate}}
\renewcommand{\headrulewidth}{0.4pt}
\renewcommand{\footrulewidth}{0.4pt}
\renewcommand{\footruleskip}{0.2in}
\pagestyle{fancy}
\fancyhead[LO]{\leftmark\ -\ \rightmark}

%%% Configuración de Listings
\lstloadlanguages{C++}
\lstnewenvironment{code}
	{%\lstset{	numbers=none, frame=lines, basicstyle=\small\ttfamily, }%
	 \csname lst@SetFirstLabel\endcsname}
	{\csname lst@SaveFirstLabel\endcsname}
\lstset{% general command to set parameter(s)
	language=C++, basicstyle=\small\ttfamily, keywordstyle=\slshape,
	emph=[1]{tipo,usa}, emphstyle={[1]\sffamily\bfseries},
	morekeywords={tint,forn,forsn},
	basewidth={0.47em,0.40em},
	columns=fixed, fontadjust, resetmargins, xrightmargin=5pt, xleftmargin=15pt,
	flexiblecolumns=false, tabsize=2, breaklines,	breakatwhitespace=false, extendedchars=true,
	numbers=left, numberstyle=\tiny, stepnumber=1, numbersep=9pt,
	frame=l, framesep=3pt,
}

\newcommand{\comb}[2]{{}_{#1}\mathrm{C}_{#2}}
\newcommand{\threepartdef}[6]
{
	\left\{
		\begin{array}{lll}
			#1 & \mbox{if } #2 \\
			#3 & \mbox{if } #4 \\
			#5 & \mbox{if } #6
		\end{array}
	\right.
}

\begin{document}

\tableofcontents\newpage

\nbtitle{(FFT) Final Fourier Tactics - Reference}
"""

LATEX_FOOTER = r"""
\newpage
\section{El Himno nacional}
Me encontraba en dif\'icil situaci\'on\\
En una prueba muy dif\'icil de mi vida \\
Estaba entre el Goloso y la DP \\
Mirando el F que no me sal\'ia  \\
Yo no queria una prueba normal \\
No me gustaban los que eran de geometr\'ia \\
El c\'odigo del C no me servia \\
Para dos rectas encontrar su intersecci\'on \\
Y tuve una revelaci\'on \\
Se calcular la geometr\'ia \\
Voy a evitar el overflow \\
\textit{Tristemente, este verso se perdio en el tiempo} \\
\\
Porque yo \\
No quiero debuggear \\
No quiero ya testear \\
No quiero submitear \\
Quiero ganarme el accepted enseguida \\
\textit{Tristemente, este verso se perdio en el tiempo} \\
\\
En la cabeza tenia arapos de mi viejo \\
Que resonaban como rulo de tambor \\
Vos, mejor que debugges \\
Mejor que programes \\
Y que obtengase 10 \\
\\
Ya me canse de que no metas los problemas \\
Voy a codearme la DP de las monedas \\
Vos mejor que debugges \\
Mejor que programes \\
Y que obtengase 10 \\
Ya me canse de ser tu fuente de algoritmos \\
\textit{El resto de la canci\'on se perdio en el tiempo} \\
\\
\\
\textit{Gracias TCA por todo lo que me enseñaste estos años} \\

\newpage
\begin{verbatim}
Baby, baby, don't look so sad
There's gonna be a better tomorrow
重い扉の向こうは
いつでも 青空さ
昨日と同じ一日が暮れて
彼女は深い溜息とともに眠る
果たせなかった約束
またひとつ増えただけ
それでも明日を夢見る
Baby, baby, close your eyes
Go back into your endless dream
目覚める頃はとっくに
笑顔が戻ってる
いい事だけを信じてるうちに
すべてを許せる自分に会える
いつか
あんなに愛した人も
愛してくれた人も
振り向けば ただの幻
Baby, baby, don't think you're lonely
Don't give up loving somebody new
繰り返される別れに
臆病にならないで
Ah, 淋しいなんて
Ah, 感じるひまもないくらい
Uh-uh-uh, uh-uh-uh, uh-uh
Uh-uh-uh, uh-uh-uh, uh-uh
果たせなかった約束
またひとつ増えただけ
それでも明日を夢見る
Baby, baby, don't look so sad
There's gonna be a better tomorrow
重い扉の向こうは
いつでも 青空さ
Baby, baby, close your eyes
Go back into your endless dream
果てしない夢の続き
見させてあげるから

竹内まりやの「夢の続き」
\end{verbatim}
\end{document}
"""

def clean_title(name):
    """
    Removes leading numbers and separators (e.g., '01_Math' -> 'Math'),
    replaces remaining underscores with spaces, and applies Title Case.
    """
    # ^\d+ matches numbers at the start. 
    # [\-_ ]* matches any underscores, dashes, or spaces right after the numbers.
    cleaned = re.sub(r'^\d+[\-_ ]*', '', name)
    return cleaned.replace('_', ' ').title()

def generate_notebook():
    with open(OUTPUT_TEX, "w", encoding="utf-8") as out:
        out.write(LATEX_HEADER)
        
        # sorted(os.walk()) ensures folders are processed alphabetically (respecting your number prefixes)
        for root, dirs, files in sorted(os.walk(SRC_DIR)):
            if root == SRC_DIR:
                continue
                
            # Gather unique base names in this specific subfolder
            base_names = set()
            for f in files:
                if f.endswith(".cpp") or f.endswith(".tex"):
                    base_names.add(os.path.splitext(f)[0])
            
            if not base_names:
                continue
                
            # Create Section title from the relative path
            # Split the path into folder names, clean each folder name, and join with " / "
            rel_path = os.path.relpath(root, SRC_DIR)
            folder_parts = rel_path.split(os.sep)
            clean_parts = [clean_title(part) for part in folder_parts]
            
            section_title = " / ".join(clean_parts)
            out.write(f"\\section{{{section_title}}}\n")
            
            # Process the files alphabetically (respecting their prefixes)
            for base_name in sorted(list(base_names)):
                # Clean the file name for the subsection title
                title = clean_title(base_name)
                out.write(f"\\subsection{{{title}}}\n")
                
                # Add Annotation (.tex)
                tex_file_path = os.path.join(root, f"{base_name}.tex")
                if os.path.exists(tex_file_path):
                    with open(tex_file_path, "r", encoding="utf-8") as tf:
                        out.write(tf.read().strip() + "\n\n")
                
                # Add Code (.cpp)
                cpp_file_path = os.path.join(root, f"{base_name}.cpp")
                if os.path.exists(cpp_file_path):
                    rel_cpp_path = cpp_file_path.replace(os.sep, '/')
                    out.write(f"\\lstinputlisting{{{rel_cpp_path}}}\n\n")

        out.write(LATEX_FOOTER)
    print(f"Successfully generated {OUTPUT_TEX}")

if __name__ == "__main__":
    generate_notebook()