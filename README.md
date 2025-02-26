O Workforce Scheduling and Routing Problem (WSRP) é um problema de otimização que combina a alocação de trabalhadores a tarefas específicas (scheduling) com a definição das melhores rotas para que eles as executem (routing). Esse problema é comum em setores como assistência técnica, serviços de saúde domiciliares e logística, onde equipes precisam atender clientes em diferentes locais dentro de um período de tempo determinado.

O objetivo do WSRP é minimizar custos operacionais, reduzir o tempo de deslocamento e melhorar a eficiência do serviço, garantindo que as tarefas sejam concluídas dentro das restrições de tempo e capacidade dos trabalhadores. 

Soluções para esse problema geralmente utilizam algoritmos de otimização, como heurísticas e metaheurísticas, para encontrar a melhor combinação entre escalonamento e roteamento.
Nesse projeto foi utilizada a busca Tabu, uma técnica de otimização baseada em busca local que utiliza um mecanismo de memória para evitar que a solução fique presa em ótimos locais. Diferente das buscas locais tradicionais, que podem estagnar ao encontrar um ótimo local, a Busca Tabu permite explorar soluções piores temporariamente para escapar dessas regiões e encontrar soluções globais melhores.

Ela funciona mantendo uma lista tabu, que armazena soluções recentemente exploradas e impede que elas sejam revisitadas por um determinado número de iterações. Além disso, a Busca Tabu pode incluir critérios de aspiração, que permitem ignorar restrições da lista tabu se uma solução significativamente melhor for encontrada.

Todo o código foi construído com Python e Jupiter notebooks
