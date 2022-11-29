%% Problem 5.8 matlab code
clc;
close all;
clear
sigma1 = [0 0.1 0.2 1 2];
sigma2 = 0:0.1:2;
sim_err_prb = zeros(1, length(sigma1));

for i = 1:length(sigma1)

    for j = 1:10000
        % simulated error rate
        [sim_err_prob, rec_sig, noise] = smldpe58(sigma1(i));
        sim_err_prb(i) = sim_err_prb(i) + sim_err_prob;
    end

    figure(2 * i - 1);
    plot(rec_sig(1:1000));
    title('Received Signal');
    figure(2 * i);
    plot(noise(1:1000));
    title('AWGN Noise');
    sim_err_prb(i) = sim_err_prb(i) / 10000;
end

theo_err_prb = zeros(1, length(sigma2));

for i = 1:length(sigma2)
    % signal-to-noise ratio
    SNR_per_bit = exp(sigma2(i));
    % theoretical error rate
    theo_err_prb(i) = (3/2) * qfunct(sqrt((4/5) * (5 / (4 * (sigma2(i))))));
end

% Plotting commands follow.
figure(11);
semilogy(sigma2, theo_err_prb, 'r', 'linewidth', 1.5);
hold on;
semilogy(sigma1, sim_err_prb, 'bo', 'linewidth', 1.5);
ylabel('Symbol Error Probability');
xlabel('Variance');
title('Serr vs Variance');
legend('Theoritical', 'Simulation');

function [p, rec_sig, noise] = smldpe58(sigmain)
    % [p]=smldPe58(snr_in_dB)
    % SMLDPE58 simulates the probability of error for the given
    % snr_in_dB, signal to noise ratio in dB.
    d = 1;
    sgma = sqrt(sigmain); % sigma, standard deviation of noise
    N = 10000; % number of symbols being simulated
    % Generation of the quaternary data source follows.
    for i = 1:N
        temp = rand; % a uniform random variable over (0,1)

        if (temp < 0.25)
            dsource(i) = 0; % With probability 1/4, source output is "00."
        elseif (temp < 0.5)
            dsource(i) = 1; % With probability 1/4, source output is "01."
        elseif (temp < 0.75)
            dsource(i) = 2; % With probability 1/4, source output is "10."
        else
            dsource(i) = 3; % With probability 1/4, source output is "11."
        end

    end

    % detection, and probability of error calculation
    numoferr = 0;
    rec_sig = zeros(1, N);
    noise = zeros(1, N);

    for i = 1:N
        % the matched filter outputs
        noise(i) = gngauss(sgma);

        if (dsource(i) == 0)
            r = -3 * d + noise(i); % if the source output is "00"
        elseif (dsource(i) == 1)
            r = -d + noise(i); % if the source output is "01"
        elseif (dsource(i) == 2)
            r = d + noise(i); % if the source output is "10"
        else
            r = 3 * d + noise(i); % if the source output is "11"
        end

        % Detector follows.
        if (r <- 2 * d)
            decis = 0; % Decision is "00."
        elseif (r < 0)
            decis = 1; % Decision is "01."
        elseif (r < 2 * d)
            decis = 2; % Decision is "10."
        else
            decis = 3; % Decision is "11."
        end

        rec_sig(i) = r;

        if (decis ~= dsource(i)) % If it is an error, increase the error counter.
            numoferr = numoferr + 1;
        end

    end

    p = numoferr / N; % probability of error estimate
end