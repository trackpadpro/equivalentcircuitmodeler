figure
bode = readtable('..\data\bode.csv');
semilogx(bode{:,1},bode{:,2}), title('Bode'), xlabel('rad/s'), ylabel('dB')

figure
nyquist = readtable('..\data\nyquist.csv');
plot(nyquist{:,1},-nyquist{:,2}), title('Nyquist'), xlabel('Real(Z)'), ylabel('Imag(Z)')

figure
bodePhase = readtable('..\data\bodePhase.csv');
subplot(211), semilogx(bodePhase{:,1},bodePhase{:,2}), title('Bode with Phase'), ylabel('dB')
subplot(212), semilogx(bodePhase{:,1},bodePhase{:,3}), xlabel('rad/s'), ylabel('rad')
