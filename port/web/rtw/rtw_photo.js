  // ---------------------------------------------------------------- P377 feature 112: photo mode's menus (rtw_photo.js)
  // The page's game-style photo mode (gmenu.js GPhoto, P366): the HUD bottom left (PHOTO MODE, view / roll / distance, the
  // controls, the buttons) and the Pose & Outfit panel on the right (P358: animation, frame, speed, model, items, what he
  // carries, face slots, parts, materials with texture and tint), in the game's font. GPhoto and main.js's `look` (the
  // choice, its name tables, lookPush -> pc_photo.c port_photo_look_set) are the page's code, copied in verbatim; only
  // main.js lookTick / lookBuild / lookRefreshValues are re-made here without the page panel. Nothing writes game memory:
  // pc_photo.c restores the hashed state on leaving photo mode whatever was chosen (as on the page).
  // Buttons only (the host's): the Menu button (or holding Photo mode half a second) gives the panel the D-pad, A and B
  // (GPhoto's "nav": the page's O / right stick click); then the D-pad moves (held: repeats, faster after a second; on
  // the long lists left / right turn a page), A chooses, B goes back (on the first page: the camera gets the D-pad again).
  // Holding Menu hides / shows the photo menus (GPhoto's "hide": the page's H). The stick, C buttons, R / Z, L, Start keep
  // working the camera, the HUD and leaving photo mode. The photo PNG never shows the menus (photo.busy, and the
  // layer's picture copy is put back first: rtw_glue.js photoCapture). Option 112, on by default.
  {
    // GPhoto names its two page inputs (main.js keyMap / keyName): here the host's extra button Menu
    const padMap = {}, keyMap = { CAMBACK: 'MENU', PHOTOUI: 'HOLD MENU' }, keyName = (v) => v, padName = (v) => v;
    // ---- page code (main.js photo name tables and `look`, gmenu.js GPhoto)
    /* @RTW_PAGE PHOTOLOOK,GPhoto@ */

    // main.js lookRefreshValues / lookBuild without the page panel: the frame count and the model signature GPhoto reads
    function lookRefreshValues() { lookUi.frames = look.anim >= 0 ? lkInfo(LR.FRAMES) : 0; }
    function lookBuild() {
      lookUi.built = true; lookUi.drawn = lkInfo(LR.DRAWN_MODEL);
      lookUi.matSig = lookUi.drawn + ':' + lkInfo(LR.MAT_N) + ':' + lkInfo(LR.TEX_N) + ':' + lkInfo(LR.DL_N) + ':' + lkInfo(LR.ATT_N);
      lookRefreshValues();
    }
    const photoUi = { shown: false };
    // main.js lookTick: every animation frame while photo mode is on (rtw_glue.js photoPoll): plays the animation,
    // follows the drawn model, runs the panel; returns the bits the camera must not see
    photoTick = function photoMenusTick(dt, d, fresh) {
      if (!photoUi.shown) return 0;
      if (!lookUi.built) { lookPush(); lookBuild(); }
      const now = performance.now();
      if (now - lookUi.lastInfo > 250) {
        lookUi.lastInfo = now;
        const sig = lkInfo(LR.DRAWN_MODEL) + ':' + lkInfo(LR.MAT_N) + ':' + lkInfo(LR.TEX_N) + ':' + lkInfo(LR.DL_N) + ':' + lkInfo(LR.ATT_N);
        if (sig !== lookUi.matSig) { lookPush(); lookBuild(); } else lookRefreshValues();
      }
      if (look.play && look.anim >= 0 && lookUi.frames > 1) {
        look.frame = (look.frame + dt * LOOK_FPS * look.speed) % (lookUi.frames - 1);
        M._port_photo_look_set(LK.FRAME, 0, Math.round(look.frame * 100));
      }
      return GPhoto.active() ? GPhoto.input(d, fresh, dt) : 0;
    };
    // main.js photoShow: photo mode started / ended
    photoShown = function photoMenusShown(on) {
      if (on && !(featureEnabled(FEATURE.PHOTOMENUS) && GameFont.load())) { log('[gphoto] photo mode without its menus (option 112 off, or no font yet)'); return; }
      if (on === photoUi.shown) return;
      photoUi.shown = on;
      if (on) { lookUi.built = false; lookUi.nav = false; }
      GPhoto.show(on);
    };
    photoToast = function photoMenusToast(text) { if (photoUi.shown && GPhoto.active()) GPhoto.toast(text); };
    // ---- hooks into the layer
    const buttonsBefore = buttonsWanted;
    buttonsWanted = () => featureEnabled(FEATURE.PHOTOMENUS) || buttonsBefore();
    hooks.input.push((d) => {   // in photo mode: Menu = the panel, holding Menu = hide the menus, holding Photo = the panel
      if (photo.state !== 2 || !photoUi.shown) return false;
      d.nav = !!(d.menuTap || d.photoHold);
      d.hide = !!d.menuHold;
      return false;   // photo mode itself takes pad 1 (rtw_glue.js photoPoll)
    });
    hooks.draw.push(() => photo.state === 2 && photoUi.shown && GPhoto.active());   // GPhoto drew in its animation frame
    hooks.state.photo = () => Object.assign({ on: featureEnabled(FEATURE.PHOTOMENUS), shown: photoUi.shown }, window.__gphoto ? window.__gphoto.state() : {});
  }
