%% Material M_Mg
% Given values for E (Young's Modulus) and nu (Poisson's ratio)
E = 50.6;   % Example value for Young's Modulus (Pa or N/m^2)
nu = 0.3;  % Example value for Poisson's ratio

% Calculate C11, C12, C22, and C44
C11 = E / (1 - nu^2);        % C11
C12 = (E * nu) / (1 - nu^2); % C12
C22 = C11;                   % C22 is equal to C11 in plane stress
C44 = E / (2 * (1 + nu));    % C44

% Display the results
disp(['C11: ', num2str(C11)]);
disp(['C12: ', num2str(C12)]);
disp(['C22: ', num2str(C22)]);
disp(['C44: ', num2str(C44)]);

%% Material M_beta
% Given values for E (Young's Modulus) and nu (Poisson's ratio)
E = 40.6;   % Example value for Young's Modulus (Pa or N/m^2)
nu = 0.3;  % Example value for Poisson's ratio

% Calculate C11, C12, C22, and C44
C11 = E / (1 - nu^2);        % C11
C12 = (E * nu) / (1 - nu^2); % C12
C22 = C11;                   % C22 is equal to C11 in plane stress
C44 = E / (2 * (1 + nu));    % C44

% Display the results
disp(['C11: ', num2str(C11)]);
disp(['C12: ', num2str(C12)]);
disp(['C22: ', num2str(C22)]);
disp(['C44: ', num2str(C44)]);