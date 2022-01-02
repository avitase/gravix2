\f[
    H(\vec{q}, \vec{p}) = \frac{p^2}{2m} + V(\vec{q}) + \lambda g(\vec{q})
\f]

\f[
    g(\vec{q}) = q^2 - 1 = 0
\f]

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
