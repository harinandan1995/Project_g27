# /usr/bin/python3
import re
fout=open("../doc/g27_lab09_report.html",'w')
fin=open("../doc/cs296_report_27.tex",'r')
fout.write("""<!DOCTYPE html>

<html>

<head>

<link rel="stylesheet" type="text/css" href="index.css">
</head>
<body>""")

cont=0
line=fin.readline()
fulltext=""
while True:
	line=fin.readline()
	if(line.find("Introduction")!=-1):
		break
while True:
	fulltext=fulltext+line
	line=fin.readline()
	if(line.find("bibliographystyle{plain}")!=-1):
		break
		
fulltext = re.sub(r"(Plots)",r'<br><div class="head3">\1</div>',fulltext)
fulltext = re.sub(r"(\\subsection\s*{)(.*)}",r'<br><div class="head1">\2</div><br><br>',fulltext)
fulltext = re.sub(r"(\\section\s*{)(.*)}",r'<br><br><div class="head0">\2</div><br>',fulltext)
ol_pattern = re.compile(r"(\\begin\s*{enumerate})(.*?)\\end\s*{enumerate}",re.DOTALL)
fulltext= re.sub(r"\\texttt{(.*?)}",r"<fontc>\1</fontc>",fulltext)#code font
descrip_pattern=re.compile(r"(\\item {\\textbf{)(.*)}}(.*)")
descrip_pattern2=re.compile(r"\\textbf\s*{(.*?)}")
#fulltext=descrip_pattern.sub(r"<b>\2</b>\3<br>",fulltext)#make items bod in the descriptive list
fulltext=descrip_pattern2.sub(r"<b>\1</b>",fulltext)#make items bold in general
fulltext = ol_pattern.sub(r"<ol>\2</ol>",fulltext) # replace \item  with <li>
fulltext = re.sub(r"(\\item)(.*)",r"<li>\2</li>",fulltext) #list items
fulltext= re.sub(r"\\\\","<br>",fulltext) #line breaks
#Table
pattern_table=re.compile(r"\\begin{table}.*?\\hline",re.DOTALL)
fulltext=pattern_table.sub(r"<br><br><table><tr><td>",fulltext)
fulltext=re.sub(r"&","<td>",fulltext)
fulltext=re.sub(r"\\hline","<tr><td>",fulltext)
pattern_tableend=re.compile(r"<tr><td>$\s*\\end{tabular}.*?table}",re.DOTALL|re.MULTILINE)
fulltext=pattern_tableend.sub(r"</table><br>",fulltext)
#Pictures
fulltext = re.sub(r"\\includegraphics\[width=([0-9]*)pt,height=([0-9]*)pt\]{(.*)}",r'<br><div class="head2">\3</div><br><img src="../data/\3.png" width="\1" height="\2" class="center"></img>',fulltext )
fulltext = re.sub(r"\\_",r"_",fulltext)
fulltext = re.sub(r"(g27)_(plot0[1-5])",r"\1_lab09_\2",fulltext)
#References
fulltext=re.sub(r"\\cite{.*}","",fulltext)
#fulltext=re.sub(r"\\_",r"\\",fulltext)
#print(fulltext)
fout.write(fulltext)
fout.write(""" </body>

</html>"""
)	