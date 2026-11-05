  // ---------------------------------------------------------------- P377 feature 111: the hold-L skip ring (rtw_ring.js)
  // The page's ring while L is held over a skippable cutscene (P321, main.js pollInput, index.html #skipring): a track,
  // an arc that fills with the hold (pc_os.c port_skip_progress, 0..1 over the 3 s), an L on a dark badge. Drawn as the
  // page's SVG (viewBox 64): right 3 %, bottom 4 % of the picture, 10 % of its height (the page: 11 % of its width, at
  // most 72 CSS pixels); the L in the game's font (white, hard shadow) once it is at hand, else the system font as the
  // SVG. Not in photo mode. Option 111, on by default (the page always shows it with Skippable cutscenes on).
  {
    const ring = { progress: 0, shown: 0 };
    const ACCENT = '#f2c14e';   // index.html --accent
    function drawRing(ctx, progress) {
      const h = layer.h, size = 0.1 * h, s = size / 64;
      const x = layer.w - 0.03 * layer.w - size, y = h - 0.04 * h - size;
      ctx.save(); ctx.translate(x, y); ctx.scale(s, s);
      ctx.lineWidth = 5;
      ctx.beginPath(); ctx.arc(32, 32, 27, 0, 2 * Math.PI); ctx.strokeStyle = 'rgba(255,255,255,.25)'; ctx.stroke();
      ctx.beginPath(); ctx.arc(32, 32, 27, -Math.PI / 2, -Math.PI / 2 + 2 * Math.PI * Math.min(1, progress)); ctx.lineCap = 'round'; ctx.strokeStyle = ACCENT; ctx.stroke();
      ctx.beginPath(); ctx.arc(32, 32, 20, 0, 2 * Math.PI); ctx.fillStyle = 'rgba(30,32,38,.8)'; ctx.fill(); ctx.lineWidth = 2; ctx.strokeStyle = 'rgba(255,255,255,.6)'; ctx.stroke();
      ctx.restore();
      if (GameFont.load()) {   // units of the viewBox: k = s canvas pixels each
        GameFont.draw(ctx, 'L', x / s + 32 + 1.4, y / s + 23 + 1.4, s, { scale: 1.6, color: '#000', alpha: 0.8, align: 'center', smooth: !!opt('smoothfont') });
        GameFont.draw(ctx, 'L', x / s + 32, y / s + 23, s, { scale: 1.6, color: '#fff', align: 'center', smooth: !!opt('smoothfont') });
      } else { ctx.fillStyle = '#fff'; ctx.font = `700 ${18 * s}px system-ui, sans-serif`; ctx.textAlign = 'center'; ctx.fillText('L', x + 32 * s, y + 38.5 * s); }
    }
    hooks.draw.push((ctx) => {
      const pr = M._port_skip_progress ? M._port_skip_progress() : 0;
      ring.progress = pr;
      if (!(pr > 0) || photo.state === 2 || !featureEnabled(FEATURE.RING)) return false;
      drawRing(ctx, pr); ring.shown++;
      return true;
    });
    hooks.state.ring = () => ({ on: featureEnabled(FEATURE.RING), progress: ring.progress, drawnTicks: ring.shown });
  }
