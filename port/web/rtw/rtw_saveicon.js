  // ---------------------------------------------------------------- P377 feature 109: the autosave icon (rtw_saveicon.js)
  // The page's option "Autosave icon" (P324, main.js flashSaveIcon, index.html #saveicon): a small floppy blinks in the top
  // right corner of the picture while the game writes its save and 1.5 s after its last block. The page sees each block
  // write (portEepDirty); here the save generation the host stores by (rtw_save_generation: EEPROM blocks written) tells.
  // Drawn as the page's SVG (viewBox 24): right 3 %, top 4 % of the picture, 6 % of its height (the page: 6 % of its
  // width, at most 40 CSS pixels), between full and 35 % opacity every 0.25 s (CSS steps(2) over 0.5 s, alternate).
  // Not in photo mode (the page hides it there: body.photo). Option 109, the page option's id here, on by default.
  {
    const icon = { generation: -1, until: 0, since: 0, shown: 0 };
    const ACCENT = '#f2c14e';   // index.html --accent
    function drawSaveIcon(ctx, now) {
      const h = layer.h, s = 0.06 * h / 24, x = layer.w - 0.03 * layer.w - 24 * s, y = 0.04 * h;
      ctx.save(); ctx.translate(x, y); ctx.scale(s, s);
      ctx.globalAlpha = Math.floor((now - icon.since) / 250) % 2 ? 0.35 : 1;
      ctx.beginPath(); ctx.moveTo(3, 3); ctx.lineTo(17, 3); ctx.lineTo(21, 7); ctx.lineTo(21, 21); ctx.lineTo(3, 21); ctx.closePath();
      ctx.fillStyle = 'rgba(30,32,38,.85)'; ctx.fill(); ctx.lineWidth = 1.6; ctx.lineJoin = 'round'; ctx.strokeStyle = '#fff'; ctx.stroke();
      ctx.fillStyle = ACCENT; ctx.fillRect(7, 3.8, 9, 5);
      ctx.fillStyle = '#fff'; ctx.beginPath(); if (ctx.roundRect) ctx.roundRect(6.5, 13, 11, 7, 1); else ctx.rect(6.5, 13, 11, 7); ctx.fill();
      ctx.restore();
    }
    hooks.draw.push((ctx, now) => {
      const gen = M._rtw_save_generation();
      if (icon.generation >= 0 && gen !== icon.generation && featureEnabled(FEATURE.SAVEICON)) {
        if (now > icon.until) { icon.since = now; log(`[saveicon] the game writes its save (generation ${gen})`); }
        icon.until = now + 1500;
      }
      icon.generation = gen;
      if (photo.state === 2 || now >= icon.until || !featureEnabled(FEATURE.SAVEICON)) return false;
      drawSaveIcon(ctx, now); icon.shown++;
      return true;
    });
    hooks.state.saveicon = () => ({ on: featureEnabled(FEATURE.SAVEICON), generation: icon.generation, showing: performance.now() < icon.until, drawnTicks: icon.shown });
  }
