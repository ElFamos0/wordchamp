import { createWebHashHistory, createRouter } from "vue-router";
import Home from "@/views/Home.vue";
import Random from "@/views/Random.vue";
import Word from "@/views/Word.vue";
import Register from "@/views/Register.vue";
import Login from "@/views/Login.vue";
import Logout from "@/views/Logout.vue";
import Choice from "@/views/Choice.vue";
import axiosAuth from '@/api/axios-auth';
import axiosRefresh from '@/api/axios-refresh';

const routes = [
  {
    path: "/",
    name: "Home",
    component: Home,
    meta: {
      title: 'Wordchamp - Maison',
      metaTags: [
        {
          name: 'description',
          content: 'Ceci est une description.'
        },
        {
          property: 'og:description',
          content: 'Ceci est une description.'
        }
      ]
    },
  },
  {
    path: "/random",
    name: "About",
    component: Random,
    meta: {
      title: 'Wordchamp - Aléatoire',
    }
  },
  {
    path: "/word",
    name: "Word",
    component: Word,
		meta: { 
      requiresAuth: true,
      title: 'Wordchamp - Le Jeu',
    }
  },
  {
    path: "/register",
    name: "Register",
    component: Register,
    meta: {
      title: 'Wordchamp - Enregistrement',
    }
  },
  {
    path: "/login",
    name: "Login",
    component: Login,
    meta: {
      title: 'Wordchamp - Connection',
    }
  },
  {
    path: "/logout",
    name: "Logout",
    component: Logout,
    meta: {
      title: 'Wordchamp - Déconnection',
    }
  },
  {
    path: "/choice",
    name: "choice-page",
    component: Choice,
    meta: {
      title: 'Blue or red pill ?',
    }
  },
];

const router = createRouter({
  history: createWebHashHistory(),
  routes,
});

function refresh_token() {
  const path = `${process.env.VUE_APP_BACKEND_URL}/refresh`;
  axiosRefresh.post(path).then(response => {
    localStorage.setItem('token', response.data.token);
    localStorage.setItem('refresh_token', response.data.refresh_token);
    localStorage.setItem('id', response.data.id);
    localStorage.setItem('username', response.data.username);
    return true
  }).catch(() => {
    return false
  });
}


router.beforeEach((to, from, next) => {
  let token = localStorage.getItem('token');
	let requireAuth = to.matched.some(record => record.meta.requiresAuth);

	if (!requireAuth) {
		next();
    return;
	}

	if (requireAuth && !token) {
		next('/login');
    return;
	}

	if (to.path === '/login') {
		if (token) {
			axiosAuth.post('/verify-token').then(() => {
				next('/word');
        return;
			}).catch(() => {
        if (refresh_token()) {
          next('/word');
          return;
        }
				next();
        return;
			});
		}
		else {
			next();
      return;
		}
	}

	if (requireAuth && token) {
		axiosAuth.post('/verify-token').then(() => {
			next();
      return;
		}).catch(() => {
      if (refresh_token()) {
        next();
        return;
      }
      next('/login');
      return;
		})
	}
  if (token) {
    axiosAuth.post('/verify-token').then(() => {
			next();
      return;
		}).catch(() => {
      if (refresh_token()) {
        next();
        return;
      }
		})
  }

  // This goes through the matched routes from last to first, finding the closest route with a title.
  // e.g., if we have `/some/deep/nested/route` and `/some`, `/deep`, and `/nested` have titles,
  // `/nested`'s will be chosen.
  const nearestWithTitle = to.matched.slice().reverse().find(r => r.meta && r.meta.title);

  // Find the nearest route element with meta tags.
  const nearestWithMeta = to.matched.slice().reverse().find(r => r.meta && r.meta.metaTags);

  const previousNearestWithMeta = from.matched.slice().reverse().find(r => r.meta && r.meta.metaTags);

  // If a route with a title was found, set the document (page) title to that value.
  if(nearestWithTitle) {
    document.title = nearestWithTitle.meta.title;
  } else if(previousNearestWithMeta) {
    document.title = previousNearestWithMeta.meta.title;
  }

  // Remove any stale meta tags from the document using the key attribute we set below.
  Array.from(document.querySelectorAll('[data-vue-router-controlled]')).map(el => el.parentNode.removeChild(el));

  // Skip rendering meta tags if there are none.
  if(!nearestWithMeta) return next();

  // Turn the meta tag definitions into actual elements in the head.
  nearestWithMeta.meta.metaTags.map(tagDef => {
    const tag = document.createElement('meta');

    Object.keys(tagDef).forEach(key => {
      tag.setAttribute(key, tagDef[key]);
    });

    // We use this to track which meta tags we create so we don't interfere with other ones.
    tag.setAttribute('data-vue-router-controlled', '');

    return tag;
  })
  // Add the meta tags to the document head.
  .forEach(tag => document.head.appendChild(tag));

  next();
});

export default router;
