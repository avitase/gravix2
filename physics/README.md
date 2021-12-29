# Physics engine of gravix2

Unit sphere:
\f[
    \begin{pmatrix}
        x \\ y \\ z
    \end{pmatrix} =
    \begin{pmatrix}
        \cos \phi \sin \lambda \\
        \cos \phi \cos \lambda \\
        \sin \phi
    \end{pmatrix}
\f]

Hamiltonian:
\f[
	H = T + V = \frac{1}{2} \left( p_\phi^2 + \frac{p_\lambda^2}{\cos^2 \phi} \right) + V
\f]

\f{align*}{
    p_\phi &= \dot \phi \\
    p_\lambda &= \dot \lambda \cos^2 \phi
\f}

\f{align*}{
    \frac{\partial H}{\partial \phi} &= \frac{\partial V}{\partial \phi} + \frac{\sin \phi}{\cos^3 \phi} \, p^2_\lambda &
    \frac{\partial H}{\partial p_\phi} &= p_\phi \\
    \frac{\partial H}{\partial \lambda} &= \frac{\partial V}{\partial \lambda} &
    \frac{\partial H}{\partial p_\lambda} &= \frac{p_\lambda}{\cos^2 \phi} \\
\f}

\f{align*}{
	V_{3\mathrm{D}} &= -\frac{1}{4\pi}\sum\limits_{i=1}^n \sum\limits_{j=0}^\infty \left( \frac{1}{2\pi j + r_i} + \frac{1}{2\pi(j+1) - r_i} \right) \\
    &= -\frac{1}{2} \sum\limits_{i=1}^n \sum\limits_{j=0}^\infty \frac{2j + 1}{(2j + 1)^2 \pi^2 - \left( r_i - \pi \right)^2}
\f}

\f[
	r_i = \arccos \sigma_i
\f]

\f[
	\sigma_i = \sin \phi \sin \phi_i + \cos \phi \cos \phi_i \cos (\lambda - \lambda_i)
\f]

\f{align*}{
    \mathrm{d}V_{3\mathrm{D}} &= \sum\limits_{i=1}^n (r_i - \pi) \sum\limits_{j=0}^\infty \frac{2j + 1}{\left[ (2j + 1)^2 \pi^2 - (r_i - \pi)^2 \right]^2} \, \mathrm{d} r_i \\
    &= \sum\limits_{i=1}^n \frac{-\sin r_i \, \mathrm{d} r_i}{\text{sinc}(r_i - \pi)} \sum\limits_{j=0}^\infty \frac{2j + 1}{\left[ (2j + 1)^2 \pi^2 - (r_i - \pi)^2 \right]^2} \\
    &= \sum\limits_{i=1}^n (-\sin r_i \, \mathrm{d} r_i) \, \mathcal{R}^{(-2)}(r_i - \pi)
\f}

\f[
	-\sin r_i \, \mathrm{d}r_i = \mathrm{d} \sigma_i
\f]

\f[
	\mathrm{d} \sigma_i = (\sin \phi \cos \phi_i \cos (\lambda - \lambda_i) - \cos \phi \sin \phi_i) \, \mathrm{d} \phi_i + \cos \phi \cos \phi_i \sin (\lambda - \lambda_i) \, \mathrm{d} \lambda_i
\f]

\f[
    \mathcal{R}^{(-2)}(x) = \frac{1}{\text{sinc}(x)} \, \sum\limits_{j=0}^\infty \frac{2j + 1}{\left[ (2j + 1)^2 \pi^2 - x^2 \right]^2}
\f]

\f[
    \mathcal{R}^{(-2)}(0) = \frac{1}{\pi^4} \sum_{j=0}^\infty \frac{1}{(2j + 1)^3} = \frac{1}{\pi^4} \left( \sum_{j=1}^\infty \frac{1}{j^3} - \sum_{j=1}^\infty \frac{1}{(2j)^3} \right) = \frac{7 \, \zeta(3)}{8 \pi^4} \approx 0.010798
\f]

\f[
    \text{sinc}(x) \, \mathcal{R}^{(-2)}(x) = \frac{1}{16 \pi^3 x} \, \left[ \psi^{(1)} \! \left( \frac{1}{2} - \frac{x}{2 \pi} \right) - \psi^{(1)} \! \left( \frac{1}{2} + \frac{x}{2 \pi} \right) \right]
\f]
\f$\psi^{(1)}\f$ is the first derivative of the digamma function

\f[
    \mathcal{R}^{(-2)}(x) = \mathcal{R}^{(-2)}(2\pi - x)
\f]
for \f$|x| \le \pi\f$ 

\f[
    (\nabla V_{3\mathrm{D}})^\top =
    \begin{pmatrix}
        V_\phi \\ V_\lambda \cos \phi
    \end{pmatrix} = 
    \sum\limits_{i=1}^n \mathcal{R}^{(-2)}(r_i - \pi)
    \begin{pmatrix}
        \sin \phi \cos \phi_i \cos (\lambda - \lambda_i) - \cos \phi \sin \phi_i \\
        \cos \phi \cos \phi_i \sin (\lambda - \lambda_i)
    \end{pmatrix}
\f]

\f[
    V_{2\mathrm{D}} = -2 \sum\limits_{i=1}^n \sum\limits_{j=0}^\infty \left[ \ln (2\pi j + r_i) + \ln (2\pi (j+1) - r_i) \right]
\f]

\f{align*}{
    \mathrm{d}V_{2\mathrm{D}} &= -2 \sum\limits_{i=1}^n \sum\limits_{j=0}^\infty \left[ \frac{1}{2\pi j + r_i} - \frac{1}{2\pi (j+1) - r_i} \right] \mathrm{d}r_i \\
    &= \sum\limits_{i=1}^n \frac{-\sin r_i \, \mathrm{d}r_i}{1 - \cos r_i} \\
    &= \sum\limits_{i=1}^n (-\sin r_i \, \mathrm{d}r_i) \, \mathcal{R}^{(-1)}(r_i - \pi) 
\f}

\f[
    \mathcal{R}^{(-1)}(x) = \frac{1}{1 + \cos x}
\f]

\f{align*}{
    (\nabla V_{2\mathrm{D}})^\top =
    \begin{pmatrix}
        V_\phi \\ V_\lambda \cos \phi
    \end{pmatrix} &= 
    \sum\limits_{i=1}^n \mathcal{R}^{(-1)}(r_i)
    \begin{pmatrix}
        \sin \phi \cos \phi_i \cos (\lambda - \lambda_i) - \cos \phi \sin \phi_i \\
        \cos \phi \cos \phi_i \sin (\lambda - \lambda_i)
    \end{pmatrix} \\
    &= \sum\limits_{i=1}^n \frac{1}{1 - \sigma_i}
    \begin{pmatrix}
        \sin \phi \cos \phi_i \cos (\lambda - \lambda_i) - \cos \phi \sin \phi_i \\
        \cos \phi \cos \phi_i \sin (\lambda - \lambda_i)
    \end{pmatrix} \\
\f}

Note that both, \f$V_{2\mathrm{D}}\f$ and \f$V_{3\mathrm{D}}\f$, are symmetric
\f{align*}{
    V_{2\mathrm{D}}(r_i) &= V_{2\mathrm{D}}(2\pi - r_i) \\
    V_{3\mathrm{D}}(r_i) &= V_{3\mathrm{D}}(2\pi - r_i)
\f}
and thus justifies our defintion of \f$\arccos \sigma_i = r_i \in [0, \pi]\f$.

Symplectic Euler:
\f{align*}{
    p'_\phi &\overset{\Phi_h}{=} p_\phi - h \left( \left( \frac{p'_\lambda}{\cos \phi} \right)^2 \tan \phi + V_\phi \right) &
    p'_\phi &\overset{\Phi_h^*}{=} p_\phi - h \left( \left( \frac{p_\lambda}{\cos \phi'} \right)^2 \tan \phi' + V'_\phi \right) \\
    p'_\lambda &\overset{\Phi_h}{=} p_\lambda - h V_\lambda \cos \phi &
    p'_\lambda &\overset{\Phi_h^*}{=} p_\lambda - h V'_\lambda \cos \phi' \\
    \phi' &\overset{\Phi_h}{=} \phi + h p_\phi' &
    \phi' &\overset{\Phi_h^*}{=} \phi + h p_\phi \\
    \lambda' &\overset{\Phi_h}{=} \lambda + h \, \frac{p_\lambda'}{\cos^2 \phi} &
    \lambda' &\overset{\Phi_h^*}{=} \lambda + h \, \frac{p_\lambda}{\cos^2 \phi'}
\f}

\f$\Phi_{\alpha h} \circ \Phi^*_{\beta h}\f$

\f{align*}{
    \phi &\leftarrow \phi + \beta h \, p_\phi \\
    \lambda &\leftarrow \lambda + \beta h \frac{p_\lambda}{\cos^2 \phi} \\
    V_\phi &\leftarrow V_\phi(\phi, \lambda) \\
    V_\lambda \cos \phi &\leftarrow V_\lambda(\phi, \lambda) \cos \phi \\
    p_\lambda &\leftarrow p_\lambda - (\alpha + \beta) h \, V_\lambda \cos \phi \\
    p_\phi &\leftarrow p_\phi - (\alpha + \beta) h \left[ V_\phi + \left( \left( \frac{p_\lambda}{\cos \phi} \right)^2 + 2 \beta h \frac{p_\lambda}{\cos \phi} V_\lambda + \beta h^2 V_\lambda^2 \right) \tan \phi \right] \\
    \lambda &\leftarrow \lambda + \alpha h \, \frac{p_\lambda}{\cos^2 \phi} \\
    \phi &\leftarrow \phi + \alpha h \, p_\phi
\f}
