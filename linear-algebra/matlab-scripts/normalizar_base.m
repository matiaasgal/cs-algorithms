% Base de entrada con lo vectores colgados
alfa = [];

% Obtenemos el orden para poder trabajar
[m, n] = size(alfa);

% Creamos una matriz que va a ser la base alfa normalizada
alfa_prima = zeros(m, n);

% Iteramos hasta la cantidad de columnas
for i = 1 : n
    % Dividimos cada vector por su norma y lo actualizo en la nueva base
    alfa_prima(:, i) = alfa(:, i) / norm(alfa(:, i));
end

disp('base ortonormal');
disp(alfa_prima);