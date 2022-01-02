\f[
    H(\vec{q}, \vec{p}) = \frac{p^2}{2m} + V(\vec{q}) + \lambda g(\vec{q})
\f]

\f{align*}{
    g(\vec{q}) &= \frac{1}{2} \left( q^2 - 1 \right) = 0 \\
    \vec\nabla g(\vec{q}) &= \vec{q}
\f}

\f{align*}{
    V_{2\mathrm{D}}(\sigma) &= -2 \sum\limits_{j=0}^\infty \big[ \ln(2\pi j + \sigma) + \ln(2\pi (j+1) - \sigma) \big] \\
    V_{3\mathrm{D}}(\sigma) &= -\frac{1}{4\pi} \sum\limits_{j=0}^\infty \left[ \frac{1}{2\pi j + \sigma} + \frac{1}{2\pi (j+1) - \sigma} \right]
\f}

\f{align*}{
    V'_{2\mathrm{D}}(\sigma) &= -\sum\limits_{i=1}^n \operatorname{cot} \frac{\sigma}{2} \\
    V'_{3\mathrm{D}}(\sigma) &= -\sum\limits_{i=1}^n (\sigma - \pi) \sum\limits_{j=0}^\infty \frac{2j + 1}{\left[ (2j+1)^2 \pi^2 - (\sigma - \pi)^2 \right]^2}
\f}

\f[
    V(\vec{q}) = \sum\limits_{i=1}^n V_d(\sigma_i)
\f]
with
\f[
    \sigma_i = \arccos(\vec{q} \cdot \vec{y}_i)
\f]

\f[
    \vec\nabla_{\!q} V(\vec{q}) = \sum\limits_{i=1}^n \frac{V'_d(\sigma_i)}{\sin \sigma_i} \, \vec{y}_i
\f]

\f{align*}{
    \frac{V'_{2\mathrm{D}}(\sigma_i)}{\sin \sigma_i} &= -\sum\limits_{i=1}^n \frac{1}{1 - \vec{q} \cdot \vec{y}_i} \\
    \frac{V'_{3\mathrm{D}}(\sigma_i)}{\sin \sigma_i} &= \sum\limits_{i=1}^n \frac{\pi - \sigma_i}{\sqrt{1 - (\vec{q} \cdot \vec{y}_i)^2}} \sum\limits_{j=0}^\infty \frac{2j + 1}{\left[ (2j+1)^2 \pi^2 - (\sigma_i - \pi)^2 \right]^2}
\f}

\f{align*}{
    H^{[1]} &= \frac{p^2}{2m} + \lambda g(\vec{q}) \\
    H^{[2]} &= V(\vec{q}) + \lambda g(\vec{q})
\f}

\f[
    \begin{pmatrix}
        \vec{q} \\ \vec{p}
    \end{pmatrix}
    \overset{\phi_t^{[1]}}{\longleftarrow}
    \begin{pmatrix}
        \frac{1}{p} \, \vec{p} \, \sin \omega t + \vec{q} \, \cos \omega t \\
        -p \, \vec{q} \, \sin \omega t + \vec{p} \, \cos \omega t
    \end{pmatrix}
\f]

\f[
    \omega = \frac{p}{m}
\f]

with approximation
\f{align*}{
    \cos x &= 1 - \frac{x^2}{2} + \mathcal{O}(x^4) \\
    \sin x &= \sqrt{1 - \cos^2(x)} = x \, \sqrt{1 - \frac{x^2}{4}} + \mathcal{O}(x^3)
\f}
\f[
    \begin{pmatrix}
        \vec{q} \\ \vec{p}
    \end{pmatrix}
    \overset{\phi_t^{[1]}}{\longleftarrow}
    \begin{pmatrix}
        \vec{q} + \frac{t}{m} \, \sqrt{1 - \frac{(\omega t)^2}{4}} \, \vec{p} - \frac{(\omega t)^2}{2} \, \vec{q} \\
        \vec{p} - m \omega^2 t \, \sqrt{1 - \frac{(\omega t)^2}{4}} \, \vec{q} - \frac{(\omega t)^2}{2} \, \vec{p}
    \end{pmatrix}
\f]

\f[
    \begin{pmatrix}
        \vec{q} \\ \vec{p}
    \end{pmatrix}
    \overset{\phi_t^{[2]}}{\longleftarrow}
    \begin{pmatrix}
        \vec{q} \\
        (\vec{q} \cdot \vec\nabla_{\!q} V(\vec{q})) \, \vec{q} \, t - \vec\nabla_{\!q} V(\vec{q}) \, t
    \end{pmatrix}
\f]

Strang splitting \f$\phi_{t/2}^{[1]} \circ \phi_t^{[2]} \circ \phi_{t/2}^{[1]}\f$
