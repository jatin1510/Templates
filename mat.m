clc;
td = 0.002;
%original sampling rate 500 Hz
t = [0:td:2.];
%time interval of 1 second
% 1Hz+3Hz sinusoids
xsig = cos(10 * pi * t) + cos(16 * pi * t);
Lsig = length(xsig);
ts = 0.02;

%inew sampling rate = 50Hz.

Nfactor = ts / td;

%send the signal through a 16-level uniform quantizer
[s_out, sq_out, sqh_out, Delta, SQNR] = sampandquant(xsig, 16, td, ts);
% calculate the Fourier transforms
Lfft = 2^ceil(log2(Lsig) + 1);
Fmax = 1 / (2 * td);
Faxis = linspace (-Fmax, Fmax, Lfft);
Xsig = fftshift (fft (xsig, Lfft));
S_out = fftshift (fft (s_out, Lfft));
%
%Examples of sampling and reconstruction using
%a) ideal impulse train through LPF
%b) flat top pulse reconstruction through LPF

%plot the original signal and the sample signals in time
%and frequency domain
figure (1);
subplot (311); sfigla = plot (t, xsig, 'k');
hold on; sfiglb = plot (t, s_out (1:Lsig), 'b'); hold off;
set (sfigla, 'Linewidth', 2); set (sfiglb, 'Linewidth', 2.);
xlabel ('time ( sec) ');
title ('Signal {\itg}_T({\itt}) and its uniform samples');
subplot (312); sfiglc = plot (Faxis, abs (Xsig));
xlabel (' frequency (Hz) ');
axis ([-150 150 0 300])
set (sfiglc, 'linewidth', 1); title('Spectrum of {\itg}_T({\itt})');
subplot (313); sfigld = plot (Faxis, abs (S_out));
xlabel ('frequency(Hz)');
axis ([-150 150 0 300 / Nfactor])
set(sfiglc, 'linewidth', 1);
title (' Spectrum of {\itg}_T({\itt})');
BW = 10; %Bandwidth i s no l arger than l 0H z .
H_lpf = zeros (1, Lfft); H_lpf (Lfft / 2 - BW:Lfft / 2 + BW - 1) = 1; % i deal LPF
S_recv = Nfactor * S_out .* H_lpf; % ideal f i l ter ing
s_recv = real(ifft (fftshift (S_recv))); % recons t ructed £ - domain
s_recv = s_recv (1:Lsig);
figure (2)
subplot(211); sfig2a = plot (Faxis, abs (S_recv));
xlabel (' frequency ( Hz ) ');
axis ([-150 150 0 60]);
title (' Spectrum of ideal filtering ( reconstruction ) ');
subplot(212); sfig2b = plot (t, xsig, 'k-.', t, s_recv (1:Lsig), 'b');
legend (' original signal ', ' reconstructed signal ');
xlabel (' time(sec)');
title (' original signal versus ideally reconstructed signal ');
set (sfig2b, 'linewidth', 2);
%non-ideal reconstruction
ZOH = ones (1, Nfactor);
s_ni = kron (downsample (s_out, Nfactor), ZOH);
S_ni = fftshift (fft (s_ni, Lfft));
S_recv2 = S_ni .* H_lpf;
%ideal filtering
s_recv2 = real (ifft (fftshift (S_recv2)));
% reconstructed f-domain
s_recv2 = s_recv2 (1:Lsig);
% reconstructed t-domain
% plot the ideally reconstructed signal in time and frequency domain
figure(3)
subplot(211); sfig3a = plot (t, xsig, 'b', t, s_ni (1:Lsig), 'b');
xlabel ('time (sec) ');
title ('original signal versus flat-top reconstruction');
subplot (212); sfig3b = plot (t, xsig, 'b', t, s_recv2 (1:Lsig), 'b--');
legend ('original signal', 'LPF reconstruction');
xlabel ('time (sec) ');
set (sfig3a, 'Linewidth', 2); set (sfig3b, 'Linewidth', 2);

title ('original and flat-top reconstruction after LPF');

function [sqnr, a_quan, code] = u_pcm(a, n)
    amax = max(abs(a));
    a_quan = a / amax;
    b_quan = a_quan;
    d = 2 / n;
    q = d .* (0:n - 1);
    q = q - ((n - 1) / 2) * d;

    for i = 1:n
        a_quan(find((q(i) - d / 2 <= a_quan) & (a_quan <= q(i) + d / 2))) = ...
            q(i) .* ones(1, length(find((q(i) - d / 2 <= a_quan) & (a_quan <= q(i) + d / 2))));
        b_quan(find(a_quan == q(i))) = (i - 1) * ones(1, length(find(a_quan == q(i))));
        End
        a_quan = a_quan * amax;
        nu = ceil(log2(n));
        code = zeros(length(a), nu);

        for i = 1:length(a)

            for j = nu:-1:0

                if (fix(b_quan(i) / (2^j)) == 1)
                    code(i, (nu - j)) = 1;
                    b_quan(i) = b_quan(i) - 2^j;
                end

            end

        end

        sqnr = 20 * log10(norm(a) / norm(a - a_quan));
        End
        Code for 8 level & 16 level
        clc;
        echo on
        t = 0:0.01:2;
        yval = zeros(1, length(t));
        f1 = @(x)(x); %Function

        f2 = @(x)(-x + 2);

        for i = 1:length(t)
            p = t(i);

            if (p >= 0) && (p < 1)
                yval(i) = f1(p);
            elseif (p >= 1) && (p < 2)
                yval(i) = f2(p);
            else
                yval(i) = 0;
            end

        end

        a = yval;
    end

    [sqnr8, aquan8, code8] = u_pcm(a, 8);
    [sqnr16, aquan16, code16] = u_pcm(a, 16);
    %Press a key to see the SQNR for N = 8
    %pause
    Sqnr8
    %pause
    % Press a key to see the SONR for N = 16
    Sqnr16
    % Press a key to see the plot of the signal and its quantized versions
    %pause

    figure;
    plot(t, a, t, aquan8, 'k-', 'linewidth', 0.8);
    legend('Original function', '8 level PCM Quantized output', 'Location', 'south');
    xlabel('Time (t)');
    ylabel('f(t) and f^{-}(t)');
    title('8 level quantized output');
    grid on;
    figure;
    plot(t, a, t, aquan16, 'k-', 'linewidth', 0.8);
    legend('Original function', '16 level PCM Quantized output', 'Location', 'south');
    xlabel('Time (t)');
    ylabel('f(t) and f^{-}(t)');
    title('16 level quantized output');
    grid on;
    figure;
    plot(t, (a - aquan8), 'k-', 'linewidth', 0.8);
    xlabel('Time (t)');
    ylabel('Quantization Error for 8 level');
    grid on;
    figure;
    plot(t, (a - aquan16), 'k-', 'linewidth', 0.8);
    xlabel('Time (t)');
    ylabel('Quantization Error for 16 level');
    grid on;

    fprintf('SQNR for 8-level Quantization %f\n\n', (sqnr8));
    fprintf('SQNR for 16-level Quantization %f\n\n', (sqnr16));
end

function [s_out, sq_out, sqh_out, Delta, SQNR] = sampandquant(sig_in, L, td, ts)

    if (rem(ts / td, 1) == 0)

        nfac = round (ts / td);
        p_zoh = ones (1, nfac);
        s_out = downsample (sig_in, nfac);
        [sq_out, Delta, SQNR] = uniquan(s_out, L);
        s_out = upsample (s_out, nfac);
        sqh_out = kron (sq_out, p_zoh);
        sq_out = upsample (sq_out, nfac);
    else
        warning ('Error! ts/td is not an integer! ');
        s_out = []; sq_out = []; sqh_out = []; Delta = []; SQNR = [];
    end

end

function [q_out, Delta, SQNR] = uniquan(sig_in, L)
    sig_pmax = max(sig_in);
    sig_nmax = min(sig_in);
    Delta = (sig_pmax - sig_nmax) / L;
    q_level = sig_nmax + Delta / 2:Delta:sig_pmax - Delta / 2; % define Q-levels
    L_sig = length(sig_in);
    sigp = (sig_in - sig_nmax) / Delta + 1/2;
    qindex = round (sigp);
    qindex = min (qindex, L);
    q_out = q_level (qindex);
    SQNR = 20 * log10 (norm(sig_in) / norm(sig_in - q_out));
end