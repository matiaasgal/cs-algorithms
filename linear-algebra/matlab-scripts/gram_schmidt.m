% Base de entrada con lo vectores colgados
alfa = [];

% Obtenemos el orden para poder trabajar
[m, n] = size(alfa);

% Creamos una matriz que va a ser la base alfa ortogonalizada
alfa_prima = zeros(m, n);

% Iteramos hasta la cantidad de columnas
for i = 1 : n
    % Agarramos 1 a 1 los vectores de la matriz original
    v_i = alfa(:, i);
    
    % Creamos un nuevo vector igual al vector que agarramos originalmente pero
    % se le haran cambios (formula de GS)
    v_i_primo = v_i;
    
    % Creamos una nueva iteracion hasta la posicion del vector anterior al
    % que estamos calculando
    for j = 1 : (i-1)
        % Agarramos nuevamente los vectores 1 a 1 de la base ortogonalizada
        v_j = alfa_prima(:,j);
        temporal = (v_i' * v_j) / (v_j' * v_j) * v_j;
        v_i_primo = v_i_primo - temporal;
    end

    % Metemos el nuevo vector a la nueva base ortogonalizada
    alfa_prima(:, i) = v_i_primo;
end

disp('Base ortogonalizada: ');
disp(rats(alfa_prima));