echo "Pareto"
cat rc201.Cordeau.50.500.0.128 | 
      sort -nr -k7,7 | tail -n 1 | awk '{print $7}' ;
      echo "- 128 - " ; 
    cat rc201.Cordeau.50.500.0.3128 | 
      sort -nr -k7,7 | tail -n 1 | awk '{print $7}' ;
      echo "- 3128 -" ; 
    cat rc201.Cordeau.50.500.0.9781 | 
      sort -nr -k7,7 | tail -n 1 | awk '{print $7}' ;
      echo "- 9781 -"

echo "Lexicographic"
cat rc201.Cordeau.50.500.1.128 | 
      sort -nr -k7,7 | tail -n 1  | awk '{print $7}' ;
      echo "- 128 - " ; 
    cat rc201.Cordeau.50.500.1.3128 | 
      sort -nr -k7,7 | tail -n 1 | awk '{print $7}' ;
      echo "- 3128 -" ; 
    cat rc201.Cordeau.50.500.1.9781 | 
      sort -nr -k7,7 | tail -n 1 | awk '{print $7}' ;
      echo "- 9781 -"

echo "Dynamic-Lexicographic"
cat rc201.Cordeau.50.500.2.128 | 
      sort -nr -k7,7 | tail -n 1 | awk '{print $7}' ;
      echo "- 128 - " ; 
    cat rc201.Cordeau.50.500.2.3128 | 
      sort -nr -k7,7 | tail -n 1 | awk '{print $7}' ;
      echo "- 3128 -" ; 
    cat rc201.Cordeau.50.500.2.9781 | 
      sort -nr -k7,7 | tail -n 1 | awk '{print $7}' ;
      echo "- 9781 -"


