    <template>
  <div class="random">
    <b-container>
        <h1>Login</h1>
        <b-row class="justify-content-md-center mt-3">
            <b-col col lg="4">
                <b-card class="mx-auto" style="max-width:350px;">
                    <b-form @submit="onSubmit" @reset="onReset">

                    <b-form-group id="username-label" label="Username:" label-for="username">
                        <b-form-input class="mx-auto" style="max-width:200px" id="username" v-model="this.form.username" placeholder="Enter username" required></b-form-input>
                    </b-form-group>

                    <b-form-group id="password-label" label="Password:" label-for="password">
                        <b-form-input class="mx-auto" style="max-width:200px" id="password" type="password" v-model="this.form.password" placeholder="Enter password" required></b-form-input>
                    </b-form-group>

                    <b-button @click="submit()" variant="primary">Login</b-button>                    </b-form>
                </b-card>
            </b-col>
        </b-row>
    </b-container>
  </div>
</template>

<script>
export default {
    name: 'loginForm',
    data() {
        return {
            form:{
                username: '',
                password: '',
            },
        }
    },
    methods: {
        submit: function() {
          this.$store.dispatch('auth/login', this.form).then(() => {
            this.$router.push('/');
          });
        },
    }
}
</script>