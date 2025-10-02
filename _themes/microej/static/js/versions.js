/*
  Adapted from the Readthedocs theme version.js template
  https://github.com/readthedocs/sphinx_rtd_theme/blob/master/sphinx_rtd_theme/static/js/versions.js_t
 */

function renderVersions(config) {
  if (!config.versions.active.length) {
    return "";
  }
  const versionsHTML = `
    <dl>
      <dt>Versions</dt>
      ${ config.versions.active.map(
      (version) => `
      <dd ${ version.slug === config.versions.current.slug ? 'class="rtd-current-item"' : '' }>
        <a href="${ version.urls.documentation }">${ version.slug }</a>
      </dd>
      `).join("\n")}
    </dl>
  `;
  return versionsHTML;
}

function renderDownloads(config) {
  if (!Object.keys(config.versions.current.downloads).length) {
    return "";
  }
  const downloadsNameDisplay = {
    pdf: "PDF"
  };

  const downloadsHTML = `
    <dl>
      <dt>Downloads</dt>
      ${ Object.entries(config.versions.current.downloads).map(
      ([name, url]) => `
        <dd>
          <a href="${ url }">${ downloadsNameDisplay[name] }</a>
        </dd>
      `).join("\n")}
    </dl>
  `;
  return downloadsHTML;
}

document.addEventListener("readthedocs-addons-data-ready", function(event) {
  const config = event.detail.data();

  const flyout = `
    <div class="rst-versions" data-toggle="rst-versions" role="note">
      <span class="rst-current-version" data-toggle="rst-current-version">
        <span class="fa fa-book"> Read the Docs</span>
        v: ${ config.versions.current.slug }
        <span class="fa fa-caret-down"></span>
      </span>
      <div class="rst-other-versions">
        <div class="injected">
          ${ renderVersions(config) }
          ${ renderDownloads(config) }
          <dl>
            <dt>Search</dt>
            <dd>
              <form id="flyout-search-form">
                <input
                  class="wy-form"
                  type="text"
                  name="q"
                  aria-label="Search docs"
                  placeholder="Search docs"
                  />
              </form>
            </dd>
          </dl>
        </div>
      </div>
  `;

  // Inject the generated flyout into the body HTML element.
  //document.body.insertAdjacentHTML("beforeend", flyout);
  document.querySelector("div.wy-grid-for-nav").insertAdjacentHTML("afterend", flyout);

  // Trigger the Read the Docs Addons Search modal when clicking on the "Search docs" input from inside the flyout.
  document.querySelector("#flyout-search-form").addEventListener("focusin", () => {
    const event = new CustomEvent("readthedocs-search-show");
    document.dispatchEvent(event);
  });

  // Trigger the Read the Docs Addons Search modal when clicking on "Search docs" input from the topnav.
  document.querySelector("#rtd-search-form").addEventListener("focusin", () => {
    const event = new CustomEvent("readthedocs-search-show");
    document.dispatchEvent(event);
  });

  // Trigger the Read the Docs Addons Search modal when clicking on "SEARCH" in the top menu
  document.querySelector("#headermicroej_LI_17").addEventListener("click", () => {
    const event = new CustomEvent("readthedocs-search-show");
    document.dispatchEvent(event);
  });

});
