  // ---------------------------------------------------------------- P377 feature 110: the customisation settings (rtw_menu.js)
  // The page's game-style menus (gmenu.js GMenu, docs/design/NATIVE_MENUS.md) in the worker: the same look (the game's red
  // title, rows in the game's font, the selected one on a red band with a pulsing >, ON in the game's yellow, help, the
  // footer's N64 button faces) and pad controls (D-pad / stick move with the game's repeat, left / right change, A or Start
  // choose, B back, closes on the main page), the same model (MenuModel over main.js OPTIONS, the Classic / Modern presets)
  // and the game's own menu sounds (gmenu.js GSound). Its own pages: no keyboard / gamepad binding pages (the host maps its
  // keys, pads and touch buttons to N64 buttons), no online rooms (the host's Online panel has them, P380: an information page), saves
  // through the host's menu (an export here too).
  // Opened by the extra button Menu (bit 21), by holding Photo mode half a second, or by the CUSTOMISATION row of the
  // game's own menus (pause, save slots, MULTI, the fireplace OPTIONS page: game C, port_set_gmenu_row /
  // port_gmenu_take_request, as in the page build). Opened by a button the game pauses (port_set_paused) as on the page;
  // from a game row the game's menu keeps running underneath with an idle pad 1. Never pauses a recording; while
  // recording the game options show locked, the game rows are off and the menu sounds silent (as the page build).
  //
  // Settings: the rows change the same values as the host's options menu (the manifest's options, rtw_option ids). The
  // host cannot be told about a change made here (no such host API), so this file keeps its own record in the game's
  // origin storage (IndexedDB 'conker-rtw', read in preRun, before the game starts): for every option the value chosen
  // here and the host's value at that time. At start the host seeds every option (rtw_option): a value chosen here wins
  // as long as the host still sends what it sent then; a different host value means the player changed it in the host's
  // menu since, so the host's wins and the record forgets that option. A change in the host's menu during play applies at
  // once and also wins. So a change in either place survives a reload; the host's menu may show an older value for an
  // option last changed here. No storage (a browser that refuses it): the host's values only, as before.
  // P378: a host with the standard 1.1 import rtw_option_changed is told about every change made here (option 116, on by
  // default): its menu shows the value at once and it stores it itself, so the record keeps only what such a host could
  // not take (an older host, or option 116 off).
  // Option 110 (on by default) switches all of this off: no menus, no rows, no sounds, the host's values only.
  {
    // ---- page code (main.js OPTIONS: labels, help, defaults)
    /* @RTW_PAGE OPTIONS@ */
    // help texts that name page keys / buttons the host does not have (the host's own defaults instead)
    const RTW_HELP = {
      photomode: 'The Photo mode button (1 on the keyboard by default, the gamepad\'s Back / View button, or its touch button) freezes the game and frees the camera, and hides the HUD. Stick: move, C buttons: look, R / Z: up and down, D-pad left / right: roll, up / down: zoom, B: back to the game\'s view, L: the game\'s HUD, A: save a PNG at twice the picture\'s resolution (in the host\'s Saved files), Start or Photo: back to the game exactly where it was. Menu: the Pose & Outfit panel. Works in cutscenes. Single player only. Off: as on the N64, no photo mode.',
      freecam: 'Single player: the C buttons (the gamepad\'s right stick) turn the camera freely around Conker: left / right orbits, up / down looks up / down, and Conker runs where the camera looks. The camera stays where you put it; the extra button "Free camera: behind" swings it back behind Conker and "Free camera: C up" is C-up (camera distance). In cutscenes, look / aim views, swimming, vehicles, fixed camera spots and multiplayer the game\'s own camera runs and they are the C buttons again. Off: as on the N64.',
      rumble: 'The game sees a Rumble Pak in each controller and the host vibrates your gamepad when the N64 one would (hits, explosions, heavy landings), where the browser supports it. Takes effect at the next level or area load. Off: no Rumble Pak. Saves are not affected.',
      togglewalk: 'The extra button "Half tilt (walk)" latches: one press walks (half stick), the next press runs again.',
      recorder: 'Records everything you press from power-on (with your save and options) into a .ckrec file for the developers\' replay tests; the extra button "Save recording" (or turning this off) hands it to the host\'s Saved files. Starts with the next start of the game. While recording the game options are fixed, free camera and photo mode are off.',
      saveicon: 'A small save icon blinks in the top right corner of the picture for 1.5 s whenever the game writes its save.',
    };
    const OPTIONS = PAGE_OPTIONS.filter((o) => KEY_ID[o.key] !== undefined).map((o) => (RTW_HELP[o.key] ? Object.assign({}, o, { help: RTW_HELP[o.key] }) : o));
    const optOf = (key) => OPTIONS.find((o) => o.key === key);
    // main.js setOption over the glue's values (rtw_option ids). P378: the host is told (standard 1.1 rtw_option_changed,
    // option 116): it shows and keeps the value itself, so the settings record forgets that option; a host that cannot be
    // told (or option 116 off): the change goes into the settings record (P377)
    function setOption(o, value) {
      const id = KEY_ID[o.key];
      if (id === undefined || !glue) return;
      const v = o.range ? Math.max(0, Math.min(100, value | 0)) : value ? 1 : 0;
      if (!glue.setOption(id, v)) return;   // the game options are fixed (recording / replay)
      if (glue.optionChanged(id, v)) { hostNow[id] = v; delete settings.chosen[id]; delete settings.hostSeen[id]; }
      else { settings.chosen[id] = v; settings.hostSeen[id] = hostValue(id); }   // the host's value now: a different one at a start = changed there
      settingsSave();
    }
    const showOptionValue = () => {};   // the page's drawer inputs: none here
    const store = { get: (k, d) => (k === 'opt.preset' ? (settings.preset || d) : d), set: (k, v) => { if (k === 'opt.preset') { settings.preset = v; settingsSave(); } } };

    // ---- page code (main.js presets, gmenu.js MenuModel)
    /* @RTW_PAGE PRESETS,MenuModel@ */

    // main.js presetShown / applyPreset / optionPicked (the drawer's buttons are gone)
    const presetMatches = (name) => PRESET_KEYS.every((k) => { const o = optOf(k); return opt(k) === PRESETS[name].values(o); });
    const presetShown = () => {
      const kept = recCfg ? null : store.get('opt.preset', null);
      if (kept === 'custom') return 'custom';
      if (PRESETS[kept] && presetMatches(kept)) return kept;
      return presetMatches('classic') ? 'classic' : presetMatches('modern') ? 'modern' : 'custom';
    };
    function applyPreset(name) {
      if (optionsLocked) return;
      store.set('opt.preset', name);
      if (name !== 'custom') for (const k of PRESET_KEYS) { const o = optOf(k), v = PRESETS[name].values(o); if (opt(k) !== v) setOption(o, v); }
      log(`[options] preset ${name} (customisation settings): ` + PRESET_KEYS.map((k) => `${k}=${+opt(k)}`).join(' '));
    }
    const optionPicked = (o) => { if (PRESET_KEYS.includes(o.key)) store.set('opt.preset', 'custom'); };
    // ---- the settings record (see the top of this file)
    const settings = { chosen: {}, hostSeen: {}, preset: null, loaded: false };
    const hostNow = {};   // id -> the value the host sent last
    const hostValue = (id) => (hostNow[id] !== undefined ? hostNow[id] : glue ? glue.value(id, 0) : 0);
    const DB = 'conker-rtw', DB_STORE = 'settings', DB_KEY = 'customisation';
    function dbOpen() {
      return new Promise((ok, no) => {
        if (typeof indexedDB === 'undefined') { no(new Error('no IndexedDB in this worker')); return; }
        const q = indexedDB.open(DB, 1);
        q.onupgradeneeded = () => q.result.createObjectStore(DB_STORE);
        q.onsuccess = () => ok(q.result); q.onerror = () => no(q.error);
      });
    }
    async function settingsLoad() {
      try {
        const db = await dbOpen();
        const v = await new Promise((ok, no) => { const q = db.transaction(DB_STORE).objectStore(DB_STORE).get(DB_KEY); q.onsuccess = () => ok(q.result); q.onerror = () => no(q.error); });
        db.close();
        if (v && typeof v === 'object') { settings.chosen = v.chosen || {}; settings.hostSeen = v.hostSeen || {}; settings.preset = v.preset || null; }
        settings.loaded = true;
        return `${Object.keys(settings.chosen).length} chosen in the customisation settings`;
      } catch (e) { settings.loaded = false; return `not kept (${e && e.message || e})`; }
    }
    let saveTimer = 0;
    function settingsSave() {
      if (saveTimer) return;
      saveTimer = setTimeout(async () => {
        saveTimer = 0;
        try {
          const db = await dbOpen();
          await new Promise((ok, no) => { const t = db.transaction(DB_STORE, 'readwrite'); t.objectStore(DB_STORE).put({ chosen: settings.chosen, hostSeen: settings.hostSeen, preset: settings.preset }, DB_KEY); t.oncomplete = ok; t.onerror = () => no(t.error); });
          db.close();
          log(`[settings] kept: ${Object.entries(settings.chosen).map(([k, v]) => `${k}=${v}`).join(' ') || 'nothing chosen here'}`);
        } catch (e) { log(`[settings] could not keep the settings: ${e && e.message || e}`); }
      }, 250);
    }
    // read the record before the game starts (preRun: the factory waits for it), at most 2 s
    {
      const pre = M['preRun'] ? [].concat(M['preRun']) : [];
      pre.push(() => {
        addRunDependency('rtw-settings');
        let done = false;
        const finish = (why) => { if (done) return; done = true; out(`[settings] ${why}`); removeRunDependency('rtw-settings'); };
        setTimeout(() => finish('not read in time: the host\'s option values only'), 2000);
        settingsLoad().then(finish, (e) => finish(String(e)));
      });
      M['preRun'] = pre;
    }
    // rtw_option from the host: the value the game should use (see the header)
    hostOption = function menuHostOption(id, value, started) {
      hostNow[id] = value;
      if (settings.chosen[id] === undefined) return value;
      if (!started && settings.hostSeen[id] === value) return settings.chosen[id];   // unchanged in the host's menu: ours
      delete settings.chosen[id]; delete settings.hostSeen[id];   // the host's menu changed it: the host's from now on
      settingsSave();
      return value;
    };

    // ---- the game's menu sounds (gmenu.js GSound) through the pulled audio
    // Same sounds and volumes as GSound; decoded read-only by pc_sfx.c port_sfx_decode, mixed into the host's pulled audio
    // by aud_out.c port_rtw_menu_sound_play. Silent while recording (the replay must not change) and with option 110 off.
    const SOUND = { move: [0x62D, 0x5DC0, 0], choose: [0x500, 0x5DC0, 0], change: [0x4FF, 0x4650, 0],
      back: [0x500, 0x4650, -500], error: [0x4FF, 0x5DC0, -1000] };   // [game sound id, play volume (of 0x7FFF), cents]
    const soundStats = { played: 0, silent: 0, none: 0, last: '' };
    snd = function menuSound(kind) {
      const k = SOUND[kind];
      if (!k) return;
      if (recCfg || netCfg || !featureOn(FEATURE.MENUS)) { soundStats.silent++; return; }   // P380: silent online (outside the lockstep)
      if (!M._port_sfx_decode || !M._port_rtw_menu_sound_play) { soundStats.none++; return; }
      const n = M._port_sfx_decode(k[0], k[2]);
      if (!n) { soundStats.none++; return; }   // the sound bank is not loaded yet (boot)
      const rate = new Float32Array(M.HEAPU8.buffer, M._port_sfx_info(), 4)[0];
      M._port_rtw_menu_sound_play(n, rate, k[1] / 0x7FFF);
      soundStats.played++; soundStats.last = kind;
    };

    // ---- the menu (rtwMenu)
    // gmenu.js GMenu's look and controls: the game's red title, rows in the game's font (selected: a red band, a pulsing >),
    // ON in the game's yellow, help below, footer with the N64 button faces. Pages: main (preset, sections, saves, online,
    // photo mode, back), one per section of MenuModel, saves, online (information only).
    const rtwMenu = (() => {
      const U = { open: false, t0: 0, stack: [], prev: -1, repeatAt: 0, helpPage: 0, helpAt: 0, helpSel: '', note: '', noteAt: 0,
        from: '', paused: false, row: -1 };
      const ROW = 15, TOP = 46, X0 = 34, X1 = 286;
      const BACK = { pause: ['Back to pause', 'Close this menu and go back to the game\'s pause menu (B or Start on this line).'],
        title: ['Back to title', 'Close this menu and go back to the title menu (B or Start on this line).'] };
      const C = { title: 'rgb(255,50,50)', text: '#ffffff', on: 'rgb(255,255,0)', off: 'rgb(170,170,170)', dim: 'rgb(150,150,150)', lock: 'rgb(120,120,120)', head: 'rgb(255,200,60)' };
      const page = () => U.stack[U.stack.length - 1];
      const fontOk = () => GameFont.load();
      const hostRow = (label, value, help) => ({ kind: 'info', label, value: typeof value === 'function' ? value : () => value, help });
      function mainItems() {
        return [MenuModel.presetItem()].concat(MenuModel.sections().filter((s) => s.id !== 'tools').map((s) => ({ kind: 'link', label: s.label, help: s.help, page: s.id })), [
          { kind: 'link', label: 'Saves', help: 'Your save is the cartridge\'s EEPROM: the host keeps it for you automatically. Export it to a file here or in the host\'s menu; import one in the host\'s menu.', page: 'saves' },
          { kind: 'link', label: 'Online', help: 'Online multiplayer: rooms are in the host\'s Online panel.', page: 'online' },   // P380
          { kind: 'action', label: 'Photo mode', help: 'Freeze the game and move a free camera; A saves a picture, Start leaves (a short press of the Photo mode button also starts it). Single player only.',
            locked: () => MenuModel.lockReason(optOf('photomode')),
            act: () => {
              const o = optOf('photomode');
              if (MenuModel.lockReason(o)) return;
              if (!opt('photomode')) { setOption(o, true); log('[options] photomode on (customisation settings)'); }
              close(); setTimeout(() => photoRequest(true), 60);
            } },
          { kind: 'link', label: 'Tools', help: MenuModel.sections().find((s) => s.id === 'tools').help.replace('Online play, the', 'The'), page: 'tools' },
          { kind: 'action', get label() { return BACK[U.from] ? BACK[U.from][0] : 'Back to game'; }, get help() { return BACK[U.from] ? BACK[U.from][1] : 'Close this menu (B, Start on this line, or the Menu button).'; }, act: () => { snd('back'); close(); } },
        ]);
      }
      function itemsOf(p) {
        if (p.id === 'main') return mainItems();
        const backRow = { kind: 'action', label: 'Back', help: 'Back to the customisation settings.', act: () => back() };
        if (p.id === 'saves') return [
          { kind: 'action', label: 'Export save', help: 'Hand your save (conker-eu.eep, the 2048-byte EEPROM image) to the host\'s Saved files, to keep it or to play it in another emulator.', act: () => exportSave() },
          hostRow('Import save', 'HOST MENU', 'To play another save, import its .eep file in the host\'s menu (Saves): the game restarts with it.'),
          backRow,
        ];
        if (p.id === 'online') return [
          // P380 standard 1.2: the host owns the rooms; the session's settings are the host menu's options 117-119
          hostRow('Online multiplayer', () => (glue.online() ? 'IN A SESSION' : glue.value(117, 1) ? 'HOST PANEL' : 'OFF'), 'Up to 4 players: one creates a room in the host\'s Online panel and shares its code or link, the others join it, the room host presses Start. Every player\'s game then starts from power-on with the room host\'s options and save (yours stays untouched). Options "Online play", "Online: own view" and "Online input delay" are in the host\'s menu.'),
          hostRow('Local multiplayer', 'MULTI', 'Up to 4 players on one screen: plug in more gamepads (the host sends them as controllers 2 to 4) and choose MULTI on the title menu.'),
          backRow,
        ];
        const s = MenuModel.sections().find((x) => x.id === p.id);
        let pre = [];
        if (p.id === 'controls') pre = [hostRow('Keys, gamepad, touch', 'HOST MENU', 'Which key, gamepad button or touch button is which N64 button is set in the host\'s menu (Controls). The Menu button (6 on the keyboard by default, or its touch button) opens these settings; holding the Photo mode button (1, the gamepad\'s Back) half a second does too.')];
        else if (p.id === 'sound') pre = [hostRow('Master volume', 'HOST MENU', 'The volume of everything is the host\'s (its menu); these are the game\'s own levels.')];
        else if (p.id === 'tools') pre = [{ kind: 'action', label: 'Replay a recording',   // P378 (standard 1.1 rtw_request_file)
          help: () => 'Watch an input recording (.ckrec, made with the Input recorder here or on the page build): the host asks you for the file (or use Open in game next to one in its Saved files). It then plays from power-on, with the recording\'s save and options, the next time the game starts (reload the page); your own save is not changed.' +
            (glue.replayPending() ? ` Ready now: "${glue.replayPending()}".` : ''),
          locked: () => glue.replayLocked(),
          act: () => { const r = glue.requestReplay(); note(r ? 'This host cannot ask for a file.' : 'Pick the recording in the host\'s window.'); } }];
        return pre.concat(s.items, [backRow]);
      }
      const TITLES = { main: 'Customisation settings', saves: 'Saves', online: 'Online' };
      const titleOf = (p) => TITLES[p.id] || MenuModel.sections().find((x) => x.id === p.id).label;
      function note(s) { U.note = String(s || ''); U.noteAt = performance.now(); }
      function exportSave() {
        const r = glue.exportSave();
        note(r ? `The host refused the file (${r}).` : 'Saved as conker-eu.eep in the host\'s Saved files.');
        log(`[gmenu] save exported${r ? ` (refused: ${r})` : ''}`);
      }
      function open(how) {
        if (U.open || !glue || !glue.started() || !featureOn(FEATURE.MENUS)) return false;
        if (photo.state === 2 || !fontOk()) return false;
        U.open = true; U.t0 = performance.now(); U.stack = [{ id: 'main', sel: 0, top: 0 }]; U.prev = -1; U.helpSel = ''; U.note = '';
        U.from = BACK[how] ? how : '';
        // single player: the game pauses as on the page (P363 / P364: not from the game's own pause / title menu, which keeps
        // running underneath with an idle pad 1); never while recording, never in an online session (P380)
        if (!U.from && !recCfg && !netCfg && !glue.hostPaused()) { U.paused = true; M._port_set_paused(1); }   // P380: never in an online session
        log(`[gmenu] open${U.from ? ` (from the game's ${U.from} menu)` : ` (${how})`}`);
        if (!U.from) snd('choose');
        return true;
      }
      function close() {
        if (!U.open) return;
        U.open = false;
        if (U.paused && !glue.hostPaused()) M._port_set_paused(0);
        U.paused = false;
        glue.maskHeld();   // buttons / the stick still held reach the game only once released
        log('[gmenu] close');
      }
      function back() { U.note = ''; snd('back'); if (U.stack.length > 1) { U.stack.pop(); U.helpSel = ''; } else close(); }
      function moveSel(d) {
        const p = page(), n = itemsOf(p).length;
        if (!n) return;
        const was = p.sel; p.sel = (p.sel + d + n) % n;
        if (p.sel !== was) snd('move');
      }
      function changeValue(item, d) {
        if (item.kind === 'toggle') return item.set(!item.get());
        if (item.kind === 'range') return item.set(item.get() + d * 5);
        if (item.kind === 'choice') { const i = item.choices.indexOf(item.get()); return item.set(item.choices[((i < 0 ? (d > 0 ? -1 : 0) : i) + d + item.choices.length) % item.choices.length]); }
      }
      function change(item, d) {
        if (!item) return;
        if (item.locked && item.locked()) { if (item.get) snd('error'); return; }
        if (!item.get) return;
        const was = item.get(), r = changeValue(item, d);
        snd(r === false || (r !== true && item.get() === was) ? 'error' : 'change');
      }
      function choose(item) {
        if (!item || item.kind === 'info') { if (item) snd('error'); return; }
        if (!/^Back/.test(item.label) && item.kind !== 'toggle' && item.kind !== 'range' && item.kind !== 'choice') snd(item.locked && item.locked() ? 'error' : 'choose');
        if (item.kind === 'link') { U.stack.push({ id: item.page, sel: 0, top: 0 }); U.helpSel = ''; U.note = ''; }
        else if (item.kind === 'action') { if (!(item.locked && item.locked())) item.act(); }
        else change(item, 1);
      }
      // the game's rows (P363 / P364 / P367): on while this feature is on and nothing records; a chosen row opens the menu
      function gameRows() {
        if (!M._port_set_gmenu_row) return;
        const on = glue.started() && featureOn(FEATURE.MENUS) && !recCfg ? 1 : 0;
        if (on !== U.row) { U.row = on; M._port_set_gmenu_row(on); log(`[gmenu] game menu customisation rows ${on ? 'on' : 'off'}`); }
        const req = M._port_gmenu_take_request();
        if (req && on && !U.open) { const how = req === 2 ? 'title' : 'pause'; if (open(how)) log(`[gmenu] opened from the ${how} menu's customisation row`); }
      }
      // pad 1 while the menu is open (true = the menu has it): D-pad / stick move (repeat 380 ms, then 90 ms), left / right
      // change, A / Start choose, B back (closes on the main page)
      function poll(d, now) {
        if (!U.open) return false;
        if (!featureOn(FEATURE.MENUS)) { close(); return false; }
        const b = d.b | 0;
        let bits = 0;
        if ((b & N64.DU) || d.y > 40) bits |= 1;
        if ((b & N64.DD) || d.y < -40) bits |= 2;
        if ((b & N64.DL) || d.x < -40) bits |= 4;
        if ((b & N64.DR) || d.x > 40) bits |= 8;
        if (b & (N64.A | N64.START)) bits |= 16;
        if (b & N64.B) bits |= 32;
        if (U.prev < 0) { U.prev = bits; return true; }   // what was held when it opened does nothing here
        const fresh = bits & ~U.prev;
        let dir = fresh & 15;
        if ((bits & 15) && (bits & 15) === (U.prev & 15)) { if (now >= U.repeatAt) { dir = bits & 15; U.repeatAt = now + 90; } }
        else U.repeatAt = now + 380;
        U.prev = bits;
        const item = itemsOf(page())[page().sel];
        if (dir & 1) moveSel(-1); else if (dir & 2) moveSel(1);
        if (dir & 4) change(item, -1); else if (dir & 8) change(item, 1);
        if (fresh & 16) choose(item); else if (fresh & 32) back();
        return true;
      }
      // gmenu.js GMenu.frame, on the layer (the picture is 240 units high, the menu a 320-unit column in its middle)
      function draw(ctx, now) {
        const w = layer.w, h = layer.h, k = h / 240, W = w / k, ox = (W - 320) / 2;
        const fade = Math.min(1, (now - U.t0) / 160);
        ctx.fillStyle = `rgba(0,0,0,${0.45 * fade})`; ctx.fillRect(0, 0, w, h);
        const g = ctx.createLinearGradient((ox + 6) * k, 0, (ox + 314) * k, 0);
        g.addColorStop(0, 'rgba(20,10,4,0)'); g.addColorStop(0.12, `rgba(20,10,4,${0.62 * fade})`); g.addColorStop(0.88, `rgba(20,10,4,${0.62 * fade})`); g.addColorStop(1, 'rgba(20,10,4,0)');
        ctx.fillStyle = g; ctx.fillRect((ox + 6) * k, 8 * k, 308 * k, 224 * k);
        const T = (s, x, y, o) => GameFont.draw(ctx, s, ox + x, y, k, Object.assign({ smooth: !!opt('smoothfont') }, o, { alpha: (o && o.alpha !== undefined ? o.alpha : 1) * fade }));
        const p = page(), items = itemsOf(p);
        T(titleOf(p), 160, 18, { scale: 1.5, color: C.title, align: 'center' });
        const pulse = 0.75 + 0.25 * Math.sin(now / 160);
        const rows = Math.max(1, Math.floor((172 - TOP) / ROW));
        if (p.sel >= items.length) p.sel = Math.max(0, items.length - 1);
        if (p.sel < p.top) p.top = p.sel;
        if (p.sel >= p.top + rows) p.top = p.sel - rows + 1;
        for (let i = p.top; i < Math.min(items.length, p.top + rows); i++) {
          const it = items[i], y = TOP + (i - p.top) * ROW, sel = i === p.sel, lock = it.locked ? it.locked() : '';
          if (sel) {
            const hb = ctx.createLinearGradient((ox + 20) * k, 0, (ox + 300) * k, 0);
            hb.addColorStop(0, 'rgba(255,60,30,0)'); hb.addColorStop(0.2, `rgba(255,60,30,${0.28 * fade})`); hb.addColorStop(0.8, `rgba(255,60,30,${0.28 * fade})`); hb.addColorStop(1, 'rgba(255,60,30,0)');
            ctx.fillStyle = hb; ctx.fillRect((ox + 20) * k, (y - 3) * k, 280 * k, (ROW - 1) * k);
            T('>', X0 - 12, y, { color: C.on, alpha: pulse });
          }
          T(it.label, X0, y, { color: lock ? C.lock : sel ? C.text : C.dim, scale: 0.85 });
          let v = '', vc = sel ? C.text : C.dim;
          if (it.kind === 'toggle') { const on = it.get(); v = on ? 'ON' : 'OFF'; vc = lock ? C.lock : on ? C.on : C.off; }
          else if (it.kind === 'range') { v = it.get() + '%'; vc = lock ? C.lock : sel ? C.on : C.off; }
          else if (it.kind === 'choice') { v = it.names(it.get()); vc = lock ? C.lock : C.on; }
          else if (it.kind === 'link') v = '>';
          else if (it.kind === 'info') v = it.value();
          if (v) {
            if (sel && !lock && (it.kind === 'range' || it.kind === 'choice')) { T('<', X1 - GameFont.measure(v, 0.85) - 9, y, { color: vc, scale: 0.85, alpha: pulse }); T('>', X1 + 4, y, { color: vc, scale: 0.85, alpha: pulse }); }
            T(v, X1, y, { color: vc, scale: 0.85, align: 'right' });
          }
        }
        if (p.top > 0) T('^', 160, TOP - 11, { color: C.dim, align: 'center', scale: 0.8 });
        if (p.top + rows < items.length) T('V', 160, TOP + rows * ROW - 2, { color: C.dim, align: 'center', scale: 0.6 });
        const it = items[p.sel], lock = it && it.locked ? it.locked() : '';
        if (U.note && now - U.noteAt > 4000) U.note = '';
        const head = U.note || lock;
        const itemHelp = it && !U.note ? (typeof it.help === 'function' ? it.help() : it.help || '') : '';
        const helpText = (head ? head + (/[.!?…:]$/.test(head) ? ' ' : '. ') : '') + itemHelp;
        const sig = p.id + ':' + p.sel + ':' + helpText;
        if (sig !== U.helpSel) { U.helpSel = sig; U.helpPage = 0; U.helpAt = now; }
        const HS = 0.7;
        let lines = GameFont.wrap(helpText, 272, HS);
        if (lines.length > 4) lines = GameFont.wrap(helpText, 256, HS);
        const pages = Math.max(1, Math.ceil(lines.length / 4));
        if (now - U.helpAt > 5000) { U.helpAt = now; U.helpPage = (U.helpPage + 1) % pages; }
        ctx.fillStyle = `rgba(0,0,0,${0.35 * fade})`; ctx.fillRect((ox + 20) * k, 170 * k, 280 * k, 46 * k);
        lines.slice(U.helpPage * 4, U.helpPage * 4 + 4).forEach((l, j) => T(l, 24, 173 + j * 10.5, { scale: HS, color: head && j === 0 && U.helpPage === 0 ? C.head : C.text, alpha: 0.92 }));
        if (pages > 1) T(`${U.helpPage + 1}/${pages}`, 296, 207, { scale: 0.5, color: C.dim, align: 'right' });
        const FS = 0.55, FY = 224;
        const btn = (x, letter, fill) => GFace.round(ctx, T, k, ox, x, FY, letter, fill, fade);
        btn(30, 'A', 'rgb(40,90,230)'); T('CHOOSE', 38, FY, { scale: FS, color: C.dim });
        const bText = U.stack.length > 1 ? 'BACK' : 'CLOSE', bw = GameFont.measure(bText, FS) + 14, bx = 160 - bw / 2;
        btn(bx + 5, 'B', 'rgb(30,160,60)'); T(bText, bx + 13, FY, { scale: FS, color: C.dim });
        const cw = GameFont.measure('CHANGE', FS);
        GFace.dpad(ctx, k, ox, 290 - cw - 8, FY, 'lr', fade); T('CHANGE', 290, FY, { scale: FS, color: C.dim, align: 'right' });
      }
      // P378 the mouse wheel (rtw_wheel, 1/100 notch, positive = down): one row per notch, as gmenu.js's wheel
      let wheelRest = 0;
      function wheel(dy) {
        if (!U.open) { wheelRest = 0; return false; }
        wheelRest += dy;
        while (Math.abs(wheelRest) >= 100) { const d = Math.sign(wheelRest); wheelRest -= d * 100; moveSel(d); }
        return true;
      }
      const state = () => ({ open: U.open, from: U.from, page: U.open ? page().id : null, sel: U.open ? page().sel : -1,
        item: U.open ? (itemsOf(page())[page().sel] || {}).label : null, rows: U.row, paused: U.paused });
      return { open, close, poll, gameRows, draw, note, state, wheel, get isOpen() { return U.open; }, get paused() { return U.paused; } };
    })();
    // ---- hooks into the layer
    hooks.attach.push(() => {   // option 110 off (the host sends it after most options): the host's values only after all
      if (featureOn(FEATURE.MENUS)) return;
      for (const id of Object.keys(settings.chosen)) if (hostNow[id] !== undefined && glue.value(+id, 0) !== hostNow[id]) glue.setOption(+id, hostNow[id]);
    });
    const buttonsBefore = buttonsWanted;
    buttonsWanted = () => featureOn(FEATURE.MENUS) || buttonsBefore();
    hooks.input.push((d, now) => {
      rtwMenu.gameRows();
      if (!featureOn(FEATURE.MENUS)) { if (rtwMenu.isOpen) rtwMenu.close(); return false; }
      if (photo.state !== 2) {
        if (d.menuPress) { if (rtwMenu.isOpen) { snd('back'); rtwMenu.close(); } else rtwMenu.open('button'); }
        else if (d.photoHold && !rtwMenu.isOpen && rtwMenu.open('hold')) log('[gmenu] opened by holding the photo mode button');
      }
      if (rtwMenu.isOpen && d.photo) { d.photo = false; snd('back'); rtwMenu.close(); }   // a short press of Photo closes it
      return rtwMenu.poll(d, now);
    });
    hooks.wheel.push((dy) => featureOn(FEATURE.MENUS) && rtwMenu.wheel(dy));   // P378
    hooks.draw.push((ctx, now) => { if (!rtwMenu.isOpen || !GameFont.load()) return false; rtwMenu.draw(ctx, now); return true; });
    hooks.hostResumed.push(() => { if (rtwMenu.isOpen && rtwMenu.paused) M._port_set_paused(1); });   // the menu still holds the game
    hooks.state.menu = () => Object.assign(rtwMenu.state(), { on: featureOn(FEATURE.MENUS), preset: presetShown(),
      sounds: Object.assign({ mixed: M._port_rtw_menu_sounds_played ? M._port_rtw_menu_sounds_played() : 0 }, soundStats),
      settings: { loaded: settings.loaded, chosen: settings.chosen, hostSeen: settings.hostSeen, preset: settings.preset } });
  }
