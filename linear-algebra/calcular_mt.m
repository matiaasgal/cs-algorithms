% Definimos la matriz a utilizar
A = [];

% Definimos una matriz identidad del mismo orden
[n,m] = size(A);
I = eye(n,m);

% Factores basicos para cada autovalor. Crear factores segun la cantidad de
% autovalores
F_1 = A - ()*I;
F_2 = A - ()*I;

% Candidato (hay que ir cambiandole las potencias)
m_candidato = F_1 * F_2;

if isequal(m_candidato, zeros(4))
    disp('El candidato SI anula la matriz, ese es el polinomio minimal');
else
    disp('El candidato NO da la matriz nula, aumentar potencias de algun autovalor');
    disp(m_candidato)
end