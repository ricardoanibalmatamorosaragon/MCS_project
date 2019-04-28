%path linux 
path_linux = "/home/ricardo/Scrivania/codeMatLab/matrici/";
%inizial memory before execute factorization
% sistemare perche per linux non ce , utilizzare top per ora memory();

matrix = { 'ex15.mat' , 'shallow_water1.mat' , 'apache2.mat' , 'parabolic_fem.mat' , 'G3_circuit.mat' , 'cfd1.mat' , 'cfd2.mat'};
%matrix = { 'ex15.mat'};
fi = fopen('/home/ricardo/Scrivania/codeMatLab/results.txt', 'w'); 


for i = 1 : length(matrix)
    tic;
    mat =load(strcat(path_linux, matrix{i}));
    load_matrix=toc;
    fprintf(fi,['matrix: ',matrix{i}, '\n' ]); 

    A=mat.Problem.A;
    fprintf(fi,['Dimensione matrice : ' ,num2str(size(A,1)),'x' ,num2str(size(A,2)),'\n']);
    n=size(A,1);
    xe=ones(n,1);
    b=A*xe;
    tic;
    x=A\b;
    time = toc;
    error = norm(x-xe)/norm(xe);
    fprintf(fi,['Tempo caricamento matrice (secondi): ', num2str(load_matrix),'\n']);
    fprintf(fi,['Tempo di computazione per cholesky (secondi): ', num2str(time),'\n']);
    fprintf(fi,['Errore relativo: ' ,num2str( error),'\n']);
    fprintf(fi,'\n');

end
fclose(fi)

